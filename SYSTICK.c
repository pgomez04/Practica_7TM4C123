/*
 * SYSTICK.c
 *
 *  Created on: 6 oct. 2021
 *      Author: juisa
 */

#include "lib/include.h"

extern void Configurar_SysTick(void){
    SysTick->CTRL = (0<<0);
    SysTick->LOAD = 0xFFFFFF - 1;
    SysTick->VAL = 0;
    SysTick->CTRL = (1<<2)|(1<<0);
}

extern void SysTick_espera(float delay){
    uint16_t i;
    for(i=0;i<(int)(delay*1000);i++){
        SysTick_1ms(50000);
    }
}

extern void SysTick_1ms(uint16_t delay){
    SysTick->CTRL = (0<<0);
    SysTick->LOAD = delay - 1;
    SysTick->VAL = 0;
    SysTick->CTRL = (1<<2)|(1<<0);
    while((SysTick->CTRL&0x00010000) == 0){}
}

