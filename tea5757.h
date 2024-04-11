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

#define TEA5757_EN PORTAbits.RA0
#define TEA5757_DATA PORTAbits.RA1
#define TEA5757_CLOCK PORTAbits.RA2
#define TEA5757_ST PORTAbits.RA3

#define TEA5757_EN_TRIS TRISAbits.RA0
#define TEA5757_DATA_TRIS TRISAbits.RA1
#define TEA5757_CLOCK_TRIS TRISAbits.RA2
#define TEA5757_ST_TRIS TRISAbits.RA3

#define TEA5757_BAND_FM 0x00
#define TEA5757_BAND_MW 0x10
#define TEA5757_BAND_LW 0x20
#define TEA5757_BAND_SW 0x30

#define TEA5757_SEARCH_DOWN 0x00
#define TEA5757_SEARCH_UP 0x01

#define TEA5757_LEVEL_0 0x00
#define TEA5757_LEVEL_1 0x01
#define TEA5757_LEVEL_2 0x02
#define TEA5757_LEVEL_3 0x03

#define TEA5757_SEARCH_DOWN 0x00
#define TEA5757_SEARCH_UP 0x01

void TEA5757_Init()
{
    TEA5757_ST_TRIS = 1; 
    TEA5757_CLOCK_TRIS = 0; 
    TEA5757_DATA_TRIS = 1; 
    TEA5757_EN_TRIS = 0; 
    
    TEA5757_EN = 0;
}

void TEA5757_Write(unsigned char data)
{
	// While WRITE-ENABLE is HIGH the microcontroller can
	// transmit data to the TEA5757; TEA5759
	
	// SET ENABLE HIGH
    TEA5757_EN = 1;
    
    // SET DATA PIN AS OUTPUT
    TEA5757_DATA_TRIS = 0;
    
    for(mask = 0x80; mask; mask >>= 1)
    {     
        
        if(data & mask) 
			TEA5757_DATA = 1; 
        else 
			TEA5757_DATA = 0; 
		
		TEA5757_CLOCK = 1; 
		__asm__ __volatile__("nop");      
        TEA5757_CLOCK = 0;
        __asm__ __volatile__("nop");
    }
    
    // SET DATA PIN AS INPUT
    TEA5757_DATA_TRIS = 1;
    
    // SET DATA HIGH
    TEA5757_DATA = 1;
    
    // SET ENABLE LOW
    TEA5757_EN = 0;    
}

void TEA5757_Set_freq(unsigned short FRQ, unsigned char LVL, 
unsigned char BND)
{
    if(BND == TEA5757_BAND_FM){
        FRQ += (unsigned short) ( (freq + 107) * 8);
    } else {
    	FRQ += (unsigned short) ( (freq + 45) * 10);
    }
    
    BND |= LVL;
    
    TEA5757_write((unsigned char)(FRQ & 0xFF)); 
	TEA5757_write((unsigned char)((FRQ >> 8) & 0xFF));
	TEA5757_write((unsigned char)BND);
}

void TEA5757_Search(unsigned char BND, unsigned char LVL, unsigned char DIR)
{
    BND |= LVL;

    if(DIR) BND |= DIR

	TEA5757_Write(0x00);
	TEA5757_Write(0x00);
    TEA5757_Write(BND);
}

#endif
