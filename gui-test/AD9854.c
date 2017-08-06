#include "AD9854.h"
#include "msp430.h"
uchar FTW1,FTW2,FTW3,FTW4,FTW5,FTW6,P_D,REF_CLK,UD_CLK1,UD_CLK2,UD_CLK3,UD_CLK4,OSKS,MD;
uchar table9854[6];
void set_sine(double freq)
{
	double f=freq;
/*
	table9854[0]=(uchar)((f*256)/160000000);//��λ
	table9854[1]=(uchar)(((f*256)/160000000-table9854[0])*256);//ȥ���������֣���ԭ�������������ٳ�256
    table9854[2]=(uchar)((((f*256)/160000000-table9854[0])*256-table9854[1])*256);
	table9854[3]=(uchar)(((((f*256)/160000000-table9854[0])*256-table9854[1])*256-table9854[2])*256);
	table9854[4]=(uchar)((((((f*256)/160000000-table9854[0])*256-table9854[1])*256-table9854[2])*256-table9854[3])*256);
	table9854[5]=(uchar)(((((((f*256)/160000000-table9854[0])*256-table9854[1])*256-table9854[2])*256-table9854[3])*256-table9854[4])*256);
*/

	table9854[0]=(uchar)((f*256)/280000000);//��λ
	table9854[1]=(uchar)(((f*256)/280000000-table9854[0])*256);//ȥ���������֣���ԭ�������������ٳ�256
    table9854[2]=(uchar)((((f*256)/280000000-table9854[0])*256-table9854[1])*256);
	table9854[3]=(uchar)(((((f*256)/280000000-table9854[0])*256-table9854[1])*256-table9854[2])*256);
	table9854[4]=(uchar)((((((f*256)/280000000-table9854[0])*256-table9854[1])*256-table9854[2])*256-table9854[3])*256);
	table9854[5]=(uchar)(((((((f*256)/280000000-table9854[0])*256-table9854[1])*256-table9854[2])*256-table9854[3])*256-table9854[4])*256);

	send_byte(PD,0x00);         //turn on I DAC and DIG,but still off Q DAC,PD: DC,DC,DC,COMP,  0,QDAC,DAC,DIG

	send_byte(FTW1_6,table9854[0]);     //����Ƶ��10MHz:15 55 46 8C 40 00
	send_byte(FTW1_5,table9854[1]);
	send_byte(FTW1_4,table9854[2]);
	send_byte(FTW1_3,table9854[3]);
	send_byte(FTW1_2,table9854[4]);
	send_byte(FTW1_1,table9854[5]);
}

//********��Ƭ����ʼ��***********//
void init_9854_port()
{
 data_dir=0xFF;
 add_dir=0xff;
 ctrl_dir=0xff;
 ctrl_out=0x32;     //CP,UDCLK,F/B/H,SK,RST=0;WR,RD,S/P=1
}
//*******************************//

//**********��ʼ��AD9854*********//
void init_9854()
{
  ctrl_out|=RST;
  delayus(1);
  ctrl_out&=~RST;
                            //1FΪĬ��ֵ����Triangle=0��QDACΪ�ڲ����룬ģʽ0���ڲ�ˢ��ʱ��
  send_byte(REFCLK,0x4e);     //PLLС��200MHz������·PLL��4��Ƶ
  delayus(4);                 //��ʱ4us���Ա�֤����д��
  send_byte(UDCLK_1,0x20);     //��ˢ�����ڸ�Ϊ600��ns����֤����1�ֽ����ݵ����ڴ���ˢ������
  delayus(2);                 //��ʱ1us���Ա�֤����д��
  send_byte(PD,0x17);     //power down����ģ��
  send_byte(OSK_S,0x00);     //����·Inv Sinc����ʹ��OSK EN
}
//*******************************//

//**********����1�ֽ�����************//
void send_byte(uchar add,uchar data)
{
  data_dir=0xff;
  ctrl_out|=WR;
  add_out=add;        //�͵�ַ
  _NOP();
  ctrl_out&=~WR;      //����WR
  data_out=data;      //������
  _NOP();
  ctrl_out|=WR;       //����WR
  delayus(1);
}
//***********************************//

//**********��ȡһ���ֽڵ�����**********//
uchar read_byte(uchar add)
{
  uchar dat;
  data_dir=0x00;
  ctrl_out|=RD;
  add_out=add;
  ctrl_out&=~RD;
  _NOP();
  dat=data_in;
  ctrl_out|=RD;
  return dat;
}
//**************************************//

//**********1us��ʱ************//
void delayus(double t)
{
  while(t--)us;
}


