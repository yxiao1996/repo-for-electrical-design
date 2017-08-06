#ifndef __DR_TFT_H_
#define __DR_TFT_H_

#include <stdint.h>

#ifndef MCLK_FREQ
  #define MCLK_FREQ 20000000
#endif

#ifndef SMCLK_FREQ
  #define SMCLK_FREQ 20000000
#endif

#define SPI_FREQ 10000000

#define TFT_XSIZE 240
#define TFT_YSIZE 320

#define TFTREG_RAM_XADDR  0x0006
#define TFTREG_RAM_YADDR  0x0007
#define TFTREG_RAM_ACCESS 0x000E

#define TFTREG_DISPLAY_CTL1 0x0000
#define TFTREG_DISPLAY_CTL2 0x0001
#define TFTREG_SOFT_RESET 0x0003
#define TFTREG_OSC_CTL    0x003A
#define TFTREG_GATE_SCN   0x0032
#define TFTREG_GATE_EN    0x003B
#define TFTREG_RAM_CTL    0x0005

#define TFTREG_WIN_MINX   0x0008
#define TFTREG_WIN_MAXX   0x0009
#define TFTREG_WIN_MINY   0x000A
#define TFTREG_WIN_MAXY   0x000B

#define TFTREG_DISPLAY_MINX   0x0029
#define TFTREG_DISPLAY_MAXX   0x002B
#define TFTREG_DISPLAY_MINY   0x002A
#define TFTREG_DISPLAY_MAXY   0x002C

//RAM_CTL
#define TFTCMD_WINMODE    0x0010 //ѡ���Ƿ�ʹ��windowģʽ
#define TFTCMD_RAMINV     0x0008 //�Ƿ�תRAM��IO����
#define TFTCMD_RAM_YMODE  0x0004 //RAM��ַ������X������Y����

//DISPLAY_CTL1

//DISPLAY_CTL2
#define TFTCMD_XADDR_INV  0x0080 //��תX��ַ
#define TFTCMD_YADDR_INV  0x0040 //��תY��ַ

/* TFT���ײ�ӿ� */

//��ʼ��TFT
void initTFT();

//��TFT������һ����ַ�������Ƿ��ͳɹ�
int tft_SendIndex(uint16_t val);

//��TFT������һ�����ݣ������Ƿ��ͳɹ�
int tft_SendData(uint16_t val);

//��TFT���ļĴ���reg��������data�������Ƿ��ͳɹ�
int tft_SendCmd(uint16_t reg, uint16_t data);

/* TFT���߲�ӿ� */
/* ���и߲�ӿ�����X��Y�Ե������ӿڴ�XΪ��YΪ�� */

//��0~255��ʾ��RGB��ɫת��ΪTFT��Ļʹ�õ���ɫ
static inline uint16_t etft_Color(uint8_t r, uint8_t g, uint8_t b)
{
  uint16_t temp = 0;
  temp |= (r << 8) & 0xF800;
  temp |= (g << 3) & 0x07E0;
  temp |= (b >> 3) & 0x001F;
  return temp;
}

//��һ��������Ϊĳ����ɫ
void etft_AreaSet(uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY, uint16_t color);

//��ָ����λ����ʾһ���ַ���
void etft_DisplayString(const char* str, uint16_t sx, uint16_t sy, uint16_t fRGB, uint16_t bRGB);

//��ָ����λ����ʾһ��ͼƬ��image��24λλͼ��������ʾ
//������˳������ҡ����µ���(����˳��ת)��ÿ3�ֽ�һ�����أ�˳��ΪB��G��R��ÿ���ֽ�����0������4��������
//�Գ���24λλͼ����0x36���Ƶ��ļ�ĩβ����
void etft_DisplayImage(const uint8_t* image, uint16_t sx, uint16_t sy, uint16_t width, uint16_t height);

#endif
