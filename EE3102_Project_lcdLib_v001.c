/*
 * File:   kasle_finalProject_lcdLib_v001.c
 * Author: jakaslewicz
 *
 * Created on May 1, 2021, 4:49 PM
 */

#include "EE3102_Project_lcdLib_v001.h"
#include "EE3102_Project_genLib_v001.h"
#include "xc.h"



void lcd_printStr(const char s[]) { // Prints the provided string 
    I2C2CONbits.SEN = 1;
    while(I2C2CONbits.SEN);
    IFS3bits.MI2C2IF = 0;
    
    I2C2TRN= 0b01111100;
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF = 0;
    
    I2C2TRN = ALL1;
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF = 0;
    
    I2C2TRN = *s;
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF = 0;
    
    s++;
    while (*s != '\0') {
        lcd_cntrl(ALL1, *s);
        s++;
    }
    
    //stop bit
    I2C2CONbits.PEN = 1;
    while(I2C2CONbits.PEN);
}

void lcd_printChar(char toPrint) {
    lcd_cmd(toPrint, RS1);
}

void lcd_setCursor(char x, char y) {
    lcd_cmd(((0b1000000 * x) + y) + 0b10000000, RS0);
}

void lcd_cmd(char command, enum ControlBits cntrl) {
    I2C2CONbits.SEN = 1;
    while(I2C2CONbits.SEN);
    IFS3bits.MI2C2IF=0;
    
    I2C2TRN= 0b01111100;
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF = 0;
    
    I2C2TRN = cntrl;
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF = 0;
    
    I2C2TRN = command;
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF = 0;
    
    I2C2CONbits.PEN = 1;
    while(I2C2CONbits.PEN);
}

void lcd_shiftScreen(enum Direction dir) {
    lcd_cmd(dir, RS0);
}

void lcd_cntrl(enum ControlBits cntrl, char data) {
    I2C2TRN = cntrl;
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF=0;
    
    I2C2TRN = data;
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF=0;
}

void lcd_init(void) {
    delay_ms(50);
    lcd_cmd(0b00111000, RS0);
    lcd_cmd(0b00111001, RS0);
    lcd_cmd(0b00010100, RS0);
    
    lcd_cmd(0b01011110, RS0);
    lcd_cmd(CONTRAST, RS0);
    
    lcd_cmd(0b01101100, RS0);
    delay_ms(200);
    lcd_cmd(0b00111000, RS0);
    lcd_cmd(0b00001100, RS0);
    lcd_cmd(0b00000001, RS0);
    delay_ms(2);
}