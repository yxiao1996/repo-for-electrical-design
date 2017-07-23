#include "AD9854.h"
#include "msp430.h"
uchar FTW1,FTW2,FTW3,FTW4,FTW5,FTW6,P_D,REF_CLK,UD_CLK1,UD_CLK2,UD_CLK3,UD_CLK4,OSKS,MD;
uchar table9854[6];
void set_sine(double freq)
{
	double f=2*freq;
	table9854[0]=(uchar)((f*256)/160000000);//高位
	table9854[1]=(uchar)(((f*256)/160000000-table9854[0])*256);//去掉整数部分，用原来的数减整数再乘256
    table9854[2]=(uchar)((((f*256)/160000000-table9854[0])*256-table9854[1])*256);
	table9854[3]=(uchar)(((((f*256)/160000000-table9854[0])*256-table9854[1])*256-table9854[2])*256);
	table9854[4]=(uchar)((((((f*256)/160000000-table9854[0])*256-table9854[1])*256-table9854[2])*256-table9854[3])*256);
	table9854[5]=(uchar)(((((((f*256)/160000000-table9854[0])*256-table9854[1])*256-table9854[2])*256-table9854[3])*256-table9854[4])*256);
	send_byte(PD,0x00);         //turn on I DAC and DIG,but still off Q DAC,PD: DC,DC,DC,COMP,  0,QDAC,DAC,DIG

	send_byte(FTW1_6,table9854[0]);     //设置频率10MHz:15 55 46 8C 40 00
	send_byte(FTW1_5,table9854[1]);
	send_byte(FTW1_4,table9854[2]);
	send_byte(FTW1_3,table9854[3]);
	send_byte(FTW1_2,table9854[4]);
	send_byte(FTW1_1,table9854[5]);
}

//********单片机初始化***********//
void init()
{
 initClock();
 data_dir=0xFF;
 add_dir=0xff;
 ctrl_dir=0xff;
 ctrl_out=0x32;     //CP,UDCLK,F/B/H,SK,RST=0;WR,RD,S/P=1
}
//*******************************//

//**********初始化AD9854*********//
void init_9854()
{
  ctrl_out|=RST;
  delayus(1);
  ctrl_out&=~RST;
                            //1F为默认值，即Triangle=0，QDAC为内部输入，模式0，内部刷新时钟
  send_byte(REFCLK,0x04);     //PLL小于200MHz，不旁路PLL，4倍频
  delayus(4);                 //延时4us，以保证数据写入
  send_byte(UDCLK_1,0x20);     //将刷新周期改为600多ns，保证发送1字节数据的周期大于刷新周期
  delayus(2);                 //延时1us，以保证数据写入
  send_byte(PD,0x17);     //power down所有模块
  send_byte(OSK_S,0x00);     //不旁路Inv Sinc，不使能OSK EN
}
//*******************************//

//**********发送1字节数据************//
void send_byte(uchar add,uchar data)
{
  data_dir=0xff;
  ctrl_out|=WR;
  add_out=add;        //送地址
  _NOP();
  ctrl_out&=~WR;      //拉低WR
  data_out=data;      //送数据
  _NOP();
  ctrl_out|=WR;       //拉高WR
  delayus(1);
}
//***********************************//

//**********读取一个字节的数据**********//
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

//**********1us延时************//
void delayus(int t)
{
  while(t--)us;
}


