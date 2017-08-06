/*
 * gui.c
 *
 *  Created on: 2017-8-6
 *      Author: xiaoy
 */
#include "gui.h"
#include "msp430.h"

//pencil pointer
unsigned int starter_x = 0;
unsigned int starter_y = 0;
unsigned int ender_x = 0;
unsigned int ender_y = 0;


void Print_Confirm(unsigned char mode)
{
	//erase previous confirmation
	unsigned box_top = (SCREEN_HIGHT / 16) * 13;
	unsigned box_bot = (SCREEN_HIGHT / 16) * 14;
	starter_x = 0;
	starter_y = box_top;
	ender_x = SCREEN_WIDTH - 1;
	ender_y = box_bot;
	DRAW_AREA;
	//print confirmation
    if(mode == 1)
    	PRINT_CONF1;
    if(mode == 2)
    	PRINT_CONF2;
}


void Refresh_OptionBox(unsigned char option, unsigned char num_box)
{
    if(option == 1)
    {
        PRINT_OPT1_INV;
        PRINT_OPT2_NOM;
    }
    if(option == 2)
    {
        PRINT_OPT2_INV;
        PRINT_OPT1_NOM;
        if(num_box >= 3)
           PRINT_OPT3_NOM;
    }
    if(option == 3)
    {
        PRINT_OPT3_INV;
        PRINT_OPT2_NOM;
        if(num_box == 4)
            PRINT_OPT4_NOM;
    }
    if(option == 4)
    {
        PRINT_OPT4_INV;
        PRINT_OPT3_NOM;
    }
}

void Draw_OptionBox(unsigned char num_box)
{
	etft_AreaSet(0, 0, SCREEN_WIDTH, SCREEN_HIGHT, COLOR_AREA);
	unsigned box_top = (SCREEN_HIGHT / 16) * 14;
	unsigned box_bot = SCREEN_HIGHT - 1;
	//draw the top and bottom lines
    starter_x = 0;
	starter_y = box_top;
	ender_x = SCREEN_WIDTH - 1;
    ender_y = box_top;
    DRAW_LINE;
    starter_x = 0;
	starter_y = box_bot;
	ender_x = SCREEN_WIDTH - 1;
    ender_y = box_bot;
    DRAW_LINE;
    //draw the deception lines
    int i = 0;
    for(i = 1; i < num_box; i++)
    {
        starter_x = (SCREEN_WIDTH / num_box) * i;
        starter_y = box_top;
        ender_x = (SCREEN_WIDTH / num_box) * i;
        ender_y = box_bot;
        DRAW_LINE;
    }
    //print options
    PRINT_OPT1_NOM;
    PRINT_OPT2_NOM;
    if(num_box >= 3)
        PRINT_OPT3_NOM;
    if(num_box == 4)
    	PRINT_OPT4_NOM;
}
