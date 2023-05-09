// @File		TEA5757.H		 		
// @Author		JOSIMAR PEREIRA LEITE
// @country		BRAZIL
// @Date		09/05/23
//
//
// Copyright (C) 2023 JOSIMAR PEREIRA LEITE
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
#ifndef TEA5757_H
#define TEA5757_H

#define TEA5757_EN              PORTAbits.RA0
#define TEA5757_DATA            PORTAbits.RA1
#define TEA5757_CLOCK           PORTAbits.RA2
#define TEA5757_ST              PORTAbits.RA3

#define TEA5757_EN_TRIS         TRISAbits.RA0
#define TEA5757_DATA_TRIS       TRISAbits.RA1
#define TEA5757_CLOCK_TRIS      TRISAbits.RA2
#define TEA5757_ST_TRIS         TRISAbits.RA3

#define TEA5757_BAND_FM         0x00000000
#define TEA5757_BAND_MW         0x00100000
#define TEA5757_BAND_LW         0x00200000
#define TEA5757_BAND_SW         0x00300000

#define TEA5757_LEVEL_0         0x00000000
#define TEA5757_LEVEL_1         0x00010000
#define TEA5757_LEVEL_2         0x00020000
#define TEA5757_LEVEL_3         0x00030000

#define TEA5757_SEARCH_DOWN     0
#define TEA5757_SEARCH_UP       1

void TEA5757_Init()
{
    TEA5757_ST_TRIS = 1; 
    TEA5757_CLOCK_TRIS = 0; 
    TEA5757_DATA_TRIS = 1; 
    TEA5757_EN_TRIS = 0; 
    
    TEA5757_EN = 0;
}

void TEA5757_Write(unsigned long data)
{
    TEA5757_EN = 1;
    TEA5757_DATA_TRIS = 0;
    
    for(unsigned long mask = 0x01000000; mask; mask >>= 1)
    {     
        TEA5757_CLOCK = 1;
        if(data & mask) TEA5757_DATA = 1; 
        else TEA5757_DATA = 0;        
        TEA5757_CLOCK = 0;
    }
    
    TEA5757_DATA_TRIS = 1;
    TEA5757_DATA = 1;
    TEA5757_EN = 0;    
}

void TEA5757_Set_freq(unsigned short freq, unsigned long level, 
unsigned long band)
{
    unsigned long data = (unsigned long) ( band | level );
    
    if(band == TEA5757_BAND_FM){
        data += (unsigned long) ( (freq + 107) * 8);
    } else {
    	data += (unsigned long) ( (freq + 45) * 10);
    }
    
    TEA5757_Write(data);
}

void TEA5757_Search(unsigned long level, unsigned long band, unsigned char dir)
{
    unsigned long data = (unsigned long) ( level | band );

    if(dir){
		data |= 0x00800000;
    }

    TEA5757_Write(data);
}

#endif
