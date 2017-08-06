/*
 * gui.h
 *
 *  Created on: 2017-8-6
 *      Author: xiaoy
 */

#ifndef GUI_H_
#define GUI_H_

//screen variables
#define SCREEN_WIDTH 320
#define SCREEN_HIGHT 240
#define COLOR_LINE  12864
#define COLOR_WORD  32768
#define COLOR_WAVE  38592
#define COLOR_AREA  0
#define WORD_MODY   5
//option names
#define OPT1  "AGC MODE"
#define OPT2  "GC MODE"
#define OPT3  "OPT3"
#define OPT4  "OPT4"
//confirmation strings
#define CONF1_STR    "Using AGC mode."
#define CONF2_STR    "Using GC mode."
//draw functions
#define DRAW_AREA    etft_AreaSet(starter_x, starter_y, ender_x, ender_y, COLOR_AREA)
#define DRAW_LINE    etft_AreaSet(starter_x, starter_y, ender_x, ender_y, COLOR_LINE)
//print functions
#define PRINT_OPT1_NOM   etft_DisplayString(OPT1, WORD_MODY, (SCREEN_HIGHT / 16) * 14 + WORD_MODY, COLOR_WORD, COLOR_AREA);
#define PRINT_OPT1_INV   etft_DisplayString(OPT1, WORD_MODY, (SCREEN_HIGHT / 16) * 14 + WORD_MODY, COLOR_AREA, COLOR_WORD);
#define PRINT_OPT2_NOM   etft_DisplayString(OPT2, (SCREEN_WIDTH / num_box) + WORD_MODY, (SCREEN_HIGHT / 16) * 14 + WORD_MODY, COLOR_WORD, COLOR_AREA);
#define PRINT_OPT2_INV   etft_DisplayString(OPT2, (SCREEN_WIDTH / num_box) + WORD_MODY, (SCREEN_HIGHT / 16) * 14 + WORD_MODY, COLOR_AREA, COLOR_WORD);
#define PRINT_OPT3_NOM   etft_DisplayString(OPT3, (SCREEN_WIDTH / num_box) * 2 + WORD_MODY, (SCREEN_HIGHT / 16) * 14 + WORD_MODY, COLOR_WORD, COLOR_AREA);
#define PRINT_OPT3_INV   etft_DisplayString(OPT3, (SCREEN_WIDTH / num_box) * 2 + WORD_MODY, (SCREEN_HIGHT / 16) * 14 + WORD_MODY, COLOR_AREA, COLOR_WORD);
#define PRINT_OPT4_NOM   etft_DisplayString(OPT4, (SCREEN_WIDTH / num_box) * 3 + WORD_MODY, (SCREEN_HIGHT / 16) * 14 + WORD_MODY, COLOR_WORD, COLOR_AREA);
#define PRINT_OPT4_INV   etft_DisplayString(OPT4, (SCREEN_WIDTH / num_box) * 3 + WORD_MODY, (SCREEN_HIGHT / 16) * 14 + WORD_MODY, COLOR_AREA, COLOR_WORD);
#define PRINT_CONF1      etft_DisplayString(CONF1_STR, WORD_MODY, (SCREEN_HIGHT / 16) * 13, COLOR_WORD, COLOR_AREA)
#define PRINT_CONF2      etft_DisplayString(CONF2_STR, WORD_MODY, (SCREEN_HIGHT / 16) * 13, COLOR_WORD, COLOR_AREA)

void Draw_OptionBox(unsigned char num_box);//option number range form 2 to 4
void Refresh_OptionBox(unsigned char option, unsigned char num_box);
void Print_Confirm(unsigned char mode);
#endif /* GUI_H_ */
