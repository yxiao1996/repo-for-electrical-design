#include <msp430.h>
#include <stdint.h>
#include "dr_i2c.h"
#include "fw_public.h"

#define OVERFLOW_ADD(val, limit) \
{ \
  val++; \
  if(val >= (limit)) \
    val = 0; \
}

#define I2C_NONE -1
#define SS_WAIT_FOR_SEND_REG 0
#define SS_WAIT_FOR_SEND_DATA 1
#define SS_WAIT_FOR_END 2
#define RS_WAIT_FOR_SEND_REG 3
#define RS_WAIT_FOR_SEND_READ_START 4
#define RS_WAIT_FOR_RECV 5
#define RS_WAIT_FOR_RECV2 6
int curI2CStatus = I2C_NONE;

void initI2C()
{
  UCB0CTL1 |= UCSWRST; //��λUCB0
  
  UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC; //7λ��ַ��������������Ϊ������I2C��ͬ��
  UCB0CTL1 = UCSSEL__SMCLK + UCSWRST; //ѡ��SMCLK��Ϊʱ�ӣ����ָ�λ
  UCB0BR0 = (SMCLK_FREQ / I2C_FREQ) & 0xFF;
  UCB0BR1 = ((SMCLK_FREQ / I2C_FREQ) >> 8) & 0xFF;
  
  P2SEL |= BIT1 + BIT2; //ѡ��P2.1��P2.2�����蹦��
  P2MAP1 = PM_UCB0SDA; //P2.1��ΪSDA
  P2MAP2 = PM_UCB0SCL; //P2.2��ΪSCL
  
  UCB0CTL1 &= ~UCSWRST; //�����λ
  
  UCB0IE |= UCNACKIE; //����NACK�ж�
}

typedef struct
{
  uint8_t slave;
  uint8_t reg;
  uint8_t value;
} I2C_TXREQ;

#define TXREQ_BUFFER_SIZE 20
I2C_TXREQ tx_requests[TXREQ_BUFFER_SIZE];
int curSendingNo = 0, curTxEmptyNo = 0;

int I2C_Send()
{
  uint16_t gie;
  _ECRIT(gie);

  if(curI2CStatus != I2C_NONE)
  {
    _LCRIT(gie);
	return 0;
  }
  
  if(curSendingNo != curTxEmptyNo)
  {
    curI2CStatus = SS_WAIT_FOR_SEND_REG; //�������״̬
    UCB0I2CSA = tx_requests[curSendingNo].slave; //�趨�ӻ���ַ
    UCB0CTL1 |= UCTR; //���÷���ģʽ
    UCB0CTL1 |= UCTXSTT; //����START
    UCB0IE |= UCTXIE; //���÷����ж�
    UCB0IE &= ~UCRXIE; //�رս����ж�
    _LCRIT(gie);
    return 1;
  }
  _LCRIT(gie);
  return 0;
}

int I2C_RequestSend(uint8_t slave, uint8_t reg, uint8_t value)
{
  uint16_t gie;
  _ECRIT(gie);

  int temp = curTxEmptyNo;
  OVERFLOW_ADD(temp, TXREQ_BUFFER_SIZE);
  if(temp == curSendingNo)
  {
    _LCRIT(gie);
	return 0; //�������ӽ����������д
  }
  
  tx_requests[curTxEmptyNo].slave = slave;
  tx_requests[curTxEmptyNo].reg = reg;
  tx_requests[curTxEmptyNo].value = value;
  
  curTxEmptyNo = temp;
  
  I2C_Send();
  
  _LCRIT(gie);
  return 1;
}

typedef struct
{
  uint8_t slave;
  uint8_t reg;
  uint16_t value;
  uint8_t hasnew;
} I2C_RXREG;

#define RXREG_BUFFER_SIZE 20
I2C_RXREG rx_regs[RXREG_BUFFER_SIZE];
int rxreg_count = 0;
int curRecvingNo = 0;

int I2C_StartQuery()
{
  if(curI2CStatus != I2C_NONE)
    return 0;
  if(rxreg_count == 0)
    return 0;
  
  int count = 0;  
  while(rx_regs[curRecvingNo].hasnew != 0)
  { //��ǰ���Ƕ�ȡ��λ�õ����ݻ�δȡ��
    OVERFLOW_ADD(curRecvingNo, rxreg_count); //������һ����
    count++;
    if(count >= rxreg_count) //��ȫ�����һ�飬����Ҫ���µĵ�
      return 0;
  }
  
  curI2CStatus = RS_WAIT_FOR_SEND_REG;
  UCB0I2CSA = rx_regs[curRecvingNo].slave; //�趨�ӻ���ַ
  UCB0CTL1 |= UCTR; //���÷���ģʽ
  UCB0CTL1 |= UCTXSTT; //����START
  UCB0IE |= UCTXIE; //���÷����ж�
  UCB0IE &= ~UCRXIE; //�رս����ж�
  return 1;
}

int I2C_AddRegQuery(uint8_t slave, uint8_t reg)
{
  uint16_t gie;
  _ECRIT(gie);

  if(rxreg_count >= RXREG_BUFFER_SIZE)
  {
    _LCRIT(gie);
    return -1; //��
  }
  
  rx_regs[rxreg_count].slave = slave;
  rx_regs[rxreg_count].reg = reg;
  rx_regs[rxreg_count].value = 0;
  rx_regs[rxreg_count].hasnew = 0;
  rxreg_count++;
  
  I2C_StartQuery();
  
  _LCRIT(gie);
  return rxreg_count-1;
}

int I2C_QueryHasNew(int index)
{
  return rx_regs[index].hasnew;
}

uint16_t I2C_CheckQuery(int index)
{
  rx_regs[index].hasnew = 0;
  uint16_t gie;
  _ECRIT(gie);
  I2C_StartQuery(); //���ڿ��Կ�ʼ�²�ѯ
  _LCRIT(gie);
  return rx_regs[index].value;
}

#pragma vector=USCI_B0_VECTOR
__interrupt void i2cInterrupt()
{
  if(UCB0IFG & UCNACKIFG)
  {
    switch(curI2CStatus)
    {
    case SS_WAIT_FOR_SEND_REG:
    case SS_WAIT_FOR_SEND_DATA:
    case SS_WAIT_FOR_END:
      OVERFLOW_ADD(curSendingNo, TXREQ_BUFFER_SIZE);
      break;
    case RS_WAIT_FOR_SEND_REG:
    case RS_WAIT_FOR_SEND_READ_START:
    case RS_WAIT_FOR_RECV:
    case RS_WAIT_FOR_RECV2:
      OVERFLOW_ADD(curRecvingNo, rxreg_count);
      break;
    default:
      break;
    }
    curI2CStatus = I2C_NONE; //��鷢������վ���Ҫ��״̬
    UCB0IFG = 0;
    if(!I2C_Send()) 
      if(!I2C_StartQuery())
        UCB0CTL1 |= UCTXSTP;
  }
  else
  {
    switch(curI2CStatus)
    {
    case SS_WAIT_FOR_SEND_REG:
      UCB0TXBUF = tx_requests[curSendingNo].reg;
      curI2CStatus = SS_WAIT_FOR_SEND_DATA;
      break;
      
    case SS_WAIT_FOR_SEND_DATA:
      UCB0TXBUF = tx_requests[curSendingNo].value;
      curI2CStatus = SS_WAIT_FOR_END;
      break;
      
    case SS_WAIT_FOR_END:
      curI2CStatus = I2C_NONE; //��鷢������վ���Ҫ��״̬
      UCB0IE &= ~UCTXIE;
      OVERFLOW_ADD(curSendingNo, TXREQ_BUFFER_SIZE);
      
      UCB0CTL1 |= UCTXSTP;
      while(UCB0CTL1 & UCTXSTP); //�ȴ�����STOP����
      __delay_cycles(100); //�ӳ�5us
      if(!I2C_Send()) 
        I2C_StartQuery();
      
      /*if(!I2C_Send()) 
        if(!I2C_StartQuery())
          UCB0CTL1 |= UCTXSTP;*/
      
      break;
      
    case RS_WAIT_FOR_SEND_REG:
      UCB0TXBUF = rx_regs[curRecvingNo].reg;
      curI2CStatus = RS_WAIT_FOR_SEND_READ_START;
      break;
      
    case RS_WAIT_FOR_SEND_READ_START:
      UCB0I2CSA = rx_regs[curRecvingNo].slave; //�趨�ӻ���ַ
      UCB0CTL1 &= ~UCTR; //���ý���ģʽ
      UCB0CTL1 |= UCTXSTT; //����START
      UCB0IE &= ~UCTXIE; //�رշ����ж�
      UCB0IE |= UCRXIE; //���������ж�
      curI2CStatus = RS_WAIT_FOR_RECV;
      break;
      
    case RS_WAIT_FOR_RECV:
      curI2CStatus = RS_WAIT_FOR_RECV2;
      rx_regs[curRecvingNo].value = UCB0RXBUF; //(UCB0RXBUF << 8) & 0xFF00;  
      UCB0CTL1 |= UCTXSTP; //��֪������һ�ֽں�ֹͣ
      break;
      
    case RS_WAIT_FOR_RECV2:
      curI2CStatus = I2C_NONE; //��鷢������վ���Ҫ��״̬
      UCB0IE &= ~UCRXIE;
      
      rx_regs[curRecvingNo].value |= (UCB0RXBUF << 8) & 0xFF00;//UCB0RXBUF;
      rx_regs[curRecvingNo].hasnew = 1;
      
      OVERFLOW_ADD(curRecvingNo, rxreg_count); //������ѯ��Ҫ��һ��ַ
      
      while(UCB0CTL1 & UCTXSTP); //�ȴ�����STOP����
      __delay_cycles(100); //�ӳ�5us
      if(!I2C_Send()) 
        I2C_StartQuery();
      
      break;
      
    default:
      break;
    }
  }
}
