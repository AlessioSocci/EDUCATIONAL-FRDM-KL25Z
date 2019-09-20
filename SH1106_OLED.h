/*
 * SSD_1306_OLED.h
 *
 *  Created on: 01 ago 2019
 *      Author: Alessio
 */

#ifndef SH1106_OLED_H_
#define SH1106_OLED_H_

#include <stdio.h>
#include "stdint.h"
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"

#include "time.h"

// OLED 132 x 64 Driver SH1106

#define SH1106_SET_COLUMN_LOWER_NIBBLE_ADDRESS      0x00
#define SH1106_SET_COLUMN_HIGHER_NIBBLE_ADDRESS     0x10


#define SH1106_SET_PAGE_0_ADDRESS          			0xB0
#define SH1106_SET_PAGE_1_ADDRESS          			0xB1
#define SH1106_SET_PAGE_2_ADDRESS          			0xB2
#define SH1106_SET_PAGE_3_ADDRESS          			0xB3
#define SH1106_SET_PAGE_4_ADDRESS          			0xB4
#define SH1106_SET_PAGE_5_ADDRESS          			0xB5
#define SH1106_SET_PAGE_6_ADDRESS          			0xB6
#define SH1106_SET_PAGE_7_ADDRESS          			0xB7


#define SH1106_DEACTIVATESCROLL           			0x2E
#define SH1106_ACTIVATESCROLL             			0x2F
#define SH1106_SETDISPLAYSTARTLINE        			0x40 // to 0x7F
#define SH1106_SETCONTRAST                			0x81
#define SH1106_CHARGEPUMP                 			0x8D
#define SH1106_SEGMENTREMAP_0_to_127  	   			0xA0
#define SH1106_SEGMENTREMAP_127_to_0              	0xA1
#define SH1106_DISPLAYALLOFF         				0xA4
#define SH1106_DISPLAYALLON               			0xA5
#define SH1106_DISPLAYNORMAL              			0xA6
#define SH1106_DISPLAYINVERSE             			0xA7
#define SH1106_SETMUXRATIO                			0xA8
#define SH1106_DISPLAYOFF                 			0xAE
#define SH1106_DISPLAYON                  			0xAF
#define SH1106_SET_DC_DC_CONTROLMODE				0xAD
#define SH1106_DC_DC_ON                  			0x8A
#define SH1106_DC_DC_OFF                  			0x8B
#define SH1106_COMSCANDIRECTION_N_to_0         		0xC0
#define SH1106_COMSCANDIRECTION_0_to_N			   	0xC8
#define SH1106_SETDISPLAYOFFSET           			0xD3
#define SH1106_SETDISPLAYCLK              			0xD5
#define SH1106_COMPINS                    			0xDA
#define SH1106_SETDESELECTLEVEL           			0xDB
#define SH1106_SETPRECHARGE							0xD9

#define SH1106_bufferLenght						(8 * 132)

#define COMMAND 									0x0
#define DATA 										0x1

void SH1106_init(void);
void SPI_sendByte(uint8_t data, uint8_t data_command);
void SH1106_setPageStart(uint8_t page);
void SH1106_setColumnStart(uint8_t column);
void SH1106_drawPixel (uint8_t xPos, uint8_t yPos);
void SH1106_flushPart(uint8_t xPosStart, uint8_t xPosStop, uint8_t yPosStart, uint8_t yPosStop);











#endif /* SH1106_OLED_H_ */
