#include "AD9854.h"
//#include "delay.h"

uchar FreqWord[6];	
uchar table9854[8];
//CLK set 1
//#define      CLK_Set            12
//const ulong  Freq_mult_ulong  = 1172812;
//const double Freq_mult_doulle = 1172812.402961067;
//CLK set 2
#define      CLK_Set            13
const ulong  Freq_mult_ulong  = 1082596;
const double Freq_mult_doulle = 1082596.064271754;

static void AD9854_WR_Byte(uchar addr,uchar data);
extern void AD9854_Init(void);
static void Freq_convert(long Freq);		
extern void AD9854_SetSine(ulong Freq,uint Shape);	
//delay function
void delay (uint us)
{
  while(us--) _NOP();
}
//variable for debug
uchar temp_data;
uchar AD9854_RD_Byte(uchar addr)
{
	uchar data;
	AD9854_DataBus_DIR = 0x00;
	AD9854_AddrBus_DIR |= BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5;
	AD9854_RD_h;
	AD9854_AddrBus_OUT = addr;
	//_NOP();
	AD9854_RD_l;
	_NOP();
//	_NOP();
//	_NOP();
	data = AD9854_DataBus_IN;
	AD9854_RD_h;
	temp_data = addr;
	return data;
}

void AD9854_WR_Byte(uchar addr,uchar data)
{
	AD9854_DataBus_DIR = 0xff;
	AD9854_AddrBus_DIR |= BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5;
	AD9854_WR_l;
	AD9854_AddrBus_OUT = addr;
	AD9854_DataBus_OUT = data;
	_NOP();
	AD9854_WR_h;
	delay(1);
	AD9854_WR_l;
	/*
	dds_data_dir=0xff;
    ad9854_wr_l;
    dds_add_out=add;//ËÍµØÖ·
    dds_data_out=data;
    _NOP();
    ad9854_wr_h;
    delay(1);
    ad9854_wr_l;
	 */
}

void AD9854_Init(void)
{
	AD9854_CtrlBus_DIR |= BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6;
	AD9854_WR_h;//
    AD9854_RD_h;
    AD9854_UDCLK_l;
    AD9854_RST_h;                 //
    delay(4);
    AD9854_RST_l;

	AD9854_WR_Byte(0x1d,0x00);	           //
	AD9854_WR_Byte(0x1e,CLK_Set);	   //¢‘
	AD9854_WR_Byte(0x1f,0x00);	   //
	AD9854_WR_Byte(0x20,0x60);	   //

	AD9854_UDCLK_h;               //
    AD9854_UDCLK_l;
}

void Freq_convert(long Freq)   
{
    ulong FreqBuf;
    ulong Temp=Freq_mult_ulong;   	       

	uchar Array_Freq[4];			     //
	Array_Freq[0]=(uchar)Freq;
	Array_Freq[1]=(uchar)(Freq>>8);
	Array_Freq[2]=(uchar)(Freq>>16);
	Array_Freq[3]=(uchar)(Freq>>24);

	FreqBuf=Temp*Array_Freq[0];                  
    FreqWord[0]=FreqBuf;    
    FreqBuf>>=8;

    FreqBuf+=(Temp*Array_Freq[1]);
    FreqWord[1]=FreqBuf;
    FreqBuf>>=8;

    FreqBuf+=(Temp*Array_Freq[2]);
    FreqWord[2]=FreqBuf;
    FreqBuf>>=8;

	FreqBuf+=(Temp*Array_Freq[3]);
    FreqWord[3]=FreqBuf;
    FreqBuf>>=8;

    FreqWord[4]=FreqBuf;
    FreqWord[5]=FreqBuf>>8;			
} 

void AD9854_SetSine(ulong Freq,uint Shape)
{
	uchar count;
	uchar Adress;

	Adress = 0x04;                        //

	Freq_convert(Freq);		           //
	/*table9854[0]=(uchar)((Freq*256)/160000000);//
	table9854[1]=(uchar)(((Freq*256)/160000000-table9854[0])*256);//
	table9854[2]=(uchar)((((Freq*256)/160000000-table9854[0])*256-table9854[1])*256);
	table9854[3]=(uchar)(((((Freq*256)/160000000-table9854[0])*256-table9854[1])*256-table9854[2])*256);
	table9854[4]=(uchar)((((((Freq*256)/160000000-table9854[0])*256-table9854[1])*256-table9854[2])*256-table9854[3])*256);
	table9854[5]=(uchar)(((((((Freq*256)/160000000-table9854[0])*256-table9854[1])*256-table9854[2])*256-table9854[3])*256-table9854[4])*256);
	FreqWord[0] = table9854[0];
	FreqWord[1] = table9854[1];
	FreqWord[2] = table9854[2];
	FreqWord[3] = table9854[3];
	FreqWord[4] = table9854[4];
	FreqWord[5] = table9854[5];*/
	for(count=6;count>0;)	          //
    {
		AD9854_WR_Byte(Adress++,FreqWord[--count]);
    }
	
	AD9854_WR_Byte(0x21,Shape>>8);	  //
	AD9854_WR_Byte(0x22,(uchar)(Shape&0xff));
	
	AD9854_WR_Byte(0x23,Shape>>8);	  //
	AD9854_WR_Byte(0x24,(uchar)(Shape&0xff));

	AD9854_UDCLK_h;                    //
    AD9854_UDCLK_l;
}
