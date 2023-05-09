// @File		CONFIG.H		 		
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
#ifndef UTILS_H
#define UTILS_H  

#define B0	0x00000001
#define B1	0x00000002
#define B2	0x00000004
#define B3	0x00000008
#define B4	0x00000010
#define B5	0x00000020
#define B6	0x00000040
#define B7	0x00000080
#define B8	0x00000100
#define B9	0x00000200
#define B10	0x00000400
#define B11	0x00000800
#define B12	0x00001000
#define B13	0x00002000
#define B14	0x00004000
#define B15	0x00008000
#define B16	0x00010000
#define B17	0x00020000
#define B18	0x00040000
#define B19	0x00080000
#define B20	0x00100000
#define B21	0x00200000
#define B22	0x00400000
#define B23	0x00800000
#define B24	0x01000000
#define B25	0x02000000
#define B26	0x04000000
#define B27	0x08000000
#define B28	0x10000000
#define B29	0x20000000
#define B30	0x40000000
#define B31	0x80000000

// CONFIG1H
#pragma config OSC = HS         
#pragma config FCMEN = OFF      
#pragma config IESO = OFF       

// CONFIG2L
#pragma config PWRT = OFF       
#pragma config BOREN = OFF      
#pragma config BORV = 3         

// CONFIG2H
#pragma config WDT = OFF        
#pragma config WDTPS = 32768    

// CONFIG3H
#pragma config CCP2MX = PORTC   
#pragma config PBADEN = OFF     
#pragma config LPT1OSC = OFF    
#pragma config MCLRE = ON       

// CONFIG4L
#pragma config STVREN = OFF     
#pragma config LVP = OFF        
#pragma config XINST = OFF      

// CONFIG5L
#pragma config CP0 = OFF        
#pragma config CP1 = OFF        
#pragma config CP2 = OFF        
#pragma config CP3 = OFF        

// CONFIG5H
#pragma config CPB = OFF        
#pragma config CPD = OFF        

// CONFIG6L
#pragma config WRT0 = OFF       
#pragma config WRT1 = OFF       
#pragma config WRT2 = OFF       
#pragma config WRT3 = OFF       

// CONFIG6H
#pragma config WRTC = OFF       
#pragma config WRTB = OFF       
#pragma config WRTD = OFF       

// CONFIG7L
#pragma config EBTR0 = OFF      
#pragma config EBTR1 = OFF      
#pragma config EBTR2 = OFF      
#pragma config EBTR3 = OFF      

// CONFIG7H
#pragma config EBTRB = OFF     

#define _XTAL_FREQ   20000000

#include <xc.h>

void PIC18F2520(void)
{
    // CLEAR PORTS
    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    
    // CLEAR DATA LATCHES
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;
    
    // A/D PORT CONFIGURAION CONTROL BIT
    // (0x0F) DIGITAL I/O
    ADCON1 = 0x0F;
    
    // TURN OFF THE COMPARATORS
    CMCON = 0x07;    
}

#endif // UTILS_H
