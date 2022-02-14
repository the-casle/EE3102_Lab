/*
 * File:   kasle_finalProject_genLib_v001.c
 * Author: jakaslewicz
 *
 * Created on May 1, 2021, 4:59 PM
 */


#include "xc.h"

void delay_ms(unsigned int ms){
    while(ms-- > 0){
        asm("repeat #15998");
        asm("nop");
    }
}

void delay_us(unsigned int us){
    while(us-- > 0){
        asm("repeat #14");
        asm("nop");
    }
}

void pic24_init(void){
    _RCDIV = 0;
    AD1PCFG = 0x9ffe;
    TRISA |= 1; // RA0 input
}

