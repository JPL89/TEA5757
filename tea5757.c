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
//#define TEA5757_ST PORTCbits.RC7

#define TEA5757_EN_TRIS TRISCbits.RC4
#define TEA5757_DATA_TRIS TRISCbits.RC6
#define TEA5757_CLOCK_TRIS TRISCbits.RC5
//#define TEA5757_ST_TRIS TRISCbits.RC7

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
#define TEA5757_SEARCH_UP 0x80

#define TEA5757_FMIF 10700000 // 10.7 MHz
#define TEA5757_AMIF 450000 // 450 KHz

void TEA5757_Init()
{
    //TEA5757_ST_TRIS = 1; 
    TEA5757_CLOCK_TRIS = 0; 
    TEA5757_DATA_TRIS = 1; 
    TEA5757_EN_TRIS = 0; 
    
    TEA5757_DATA = 1; 
    TEA5757_CLOCK = 0;
    TEA5757_EN = 0;
}

void TEA5757_Write(unsigned long data)
{	        
    TEA5757_EN = 1;
    
    // SET DATA AS OUTPUT
    TEA5757_DATA_TRIS = 0;
    
    // To write the entire shift register 25 clock pulses are necessary
    // MSB FIRST
    for(unsigned long mask = 0x1000000; mask; mask >>= 1)
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
    
    // PULL-UP
    TEA5757_DATA = 1;
    
    // SET ENABLE LOW
    TEA5757_EN = 0;    
}

unsigned long TEA5757_Read(void)
{
	unsigned long data = 0x00000000;
    
    TEA5757_EN = 1;
    __asm__ __volatile__("nop"); 
    TEA5757_EN = 0;
    
    for(unsigned long mask = 0x1000000; mask; mask >>= 1)
    {                 
        data <<= 1;
		if(TEA5757_DATA)             
            data |= 0x0000001;
		
        TEA5757_CLOCK = 1; 
		__asm__ __volatile__("nop"); 
        TEA5757_CLOCK = 0;
        __asm__ __volatile__("nop");
    }
    
    return ((unsigned long) (data));
}

void TEA5757_Set_freq(unsigned long FREQUENCY, unsigned char BAND, unsigned char LEVEL)
{
    unsigned long data = 0x00000000;
        
    data |= (unsigned long) (BAND);
    data |= (unsigned long) (LEVEL); 
    data |= (unsigned long) (TEA5757_PORT_18); // SEE DATASHEET
    data |= (unsigned long) (TEA5757_PORT_19); // SEE DATASHEET
	data |= (unsigned long) (data << 16);
    
    if(BAND == TEA5757_BAND_FM)    
        // FM VALUE + FMIF / 12.5 KHz
        // FM VALUE: 88000000 - 108000000
        data |= (unsigned long) ( (FREQUENCY + TEA5757_FMIF) / 12500);    
    else     
        // AM VALUE + AMIF / 1 khz
        // AM VALUE: 53000 - 170000
    	data |= (unsigned long) ( (FREQUENCY + TEA5757_AMIF) / 1000);        
    
    TEA5757_Write(data);        
}

unsigned long TEA5757_Get_freq(void)
{
    unsigned long data = (unsigned long) TEA5757_Read();    
    return ( (unsigned long) (data & 0x00007FFF));    
}

void TEA5757_Search(unsigned char BAND, unsigned char LEVEL, unsigned char DIRECTION)
{
    unsigned long data = 0x00000000;
        
    data |= (unsigned long) (BAND);
    data |= (unsigned long) (LEVEL);
    data |= (unsigned long) (DIRECTION);
    data |= (unsigned long) (data << 16);
    
    // SERCH START/END
    data |= (unsigned long) 0x1000000;
    
	TEA5757_Write(data);
}

#endif

