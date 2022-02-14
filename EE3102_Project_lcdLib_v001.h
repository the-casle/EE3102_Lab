/* 
 * File:   kasle_finalProject_lcdLib_v001.h
 * Author: jakaslewicz
 *
 * Created on May 1, 2021, 4:50 PM
 */

#ifndef KASLE_FINALPROJECT_LCDLIB_V001_H
#define	KASLE_FINALPROJECT_LCDLIB_V001_H

#ifdef	__cplusplus
extern "C" {
#endif
const static char CONTRAST = 0b01110000;
const static enum ControlBits {
    RS1 = 0b01000000,
    RS0 = 0b00000000,
    ALL1 = 0b11000000
} ControlBits;
const static enum Direction {
    LEFT = 0b00011000,
    RIGHT = 0b00011100
} Direction;

void delay_ms(unsigned int);
void lcd_printChar(char);
void lcd_setCursor(char, char);
void lcd_cmd(char, enum ControlBits);
void lcd_init(void);
void lcd_printStr(const char *s);
void lcd_cntrl(enum ControlBits, char);
void lcd_shiftScreen(enum Direction);

#ifdef	__cplusplus
}
#endif

#endif	/* KASLE_FINALPROJECT_LCDLIB_V001_H */

