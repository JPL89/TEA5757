// @File		TEA5757.H		 		
// @Author		JOSIMAR PEREIRA LEITE
// @country		BRAZIL
// @Date		10/04/24
//
//
// Copyright (C) 2024 JOSIMAR PEREIRA LEITE
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
#ifndef TEA5757_H
#define TEA5757_H

#define TEA5757_EN PORTCbits.RC4
#define TEA5757_DATA PORTCbits.RC6
#define TEA5757_CLOCK PORTCbits.RC5

#define TEA5757_EN_TRIS TRISCbits.RC4
#define TEA5757_DATA_TRIS TRISCbits.RC6
#define TEA5757_CLOCK_TRIS TRISCbits.RC5

#define TEA5757_LEVEL_0 0x00
#define TEA5757_LEVEL_1 0x01
#define TEA5757_LEVEL_2 0x02
#define TEA5757_LEVEL_3 0x03

#define TEA5757_PORT_18 0x04
#define TEA5757_PORT_19 0x08

#define TEA5757_BAND_FM 0x00
#define TEA5757_BAND_MW 0x10
#define TEA5757_BAND_LW 0x20
#define TEA5757_BAND_SW 0x30

#define TEA5757_SEARCH_DOWN 0x00
#define TEA5757_SEARCH_UP 0x01

#define TEA5757_FMIF 10700000 // 10.7 MHz
#define TEA5757_AMIF 450000 // 450 KHz

void TEA5757_Init();
void TEA5757_Write(unsigned long data);
unsigned long TEA5757_Read(void);
void TEA5757_Set_freq(unsigned long FREQUENCY, unsigned char BAND, unsigned char LEVEL);
unsigned long TEA5757_Get_freq(void);  
void TEA5757_Search(unsigned char BND, unsigned char LVL, unsigned char DIR);

#endif

