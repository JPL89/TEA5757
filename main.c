// @File		MAIN.C		 		
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
#include "utils.h"
#include "tea5757.h"

void main(void)
{
    __delay_ms(500);  
    
    PIC18F2520();  
    
    TEA5757_Init(); 
    
    TEA5757_Set_freq(1029, TEA5757_LEVEL_3, TEA5757_BAND_FM);
    
    while(1);
    
    return;
}
