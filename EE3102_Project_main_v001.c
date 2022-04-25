/*
 * File:   kasle_lab6_main_v001.c
 * Author: jakaslewicz
 *
 * Created on April 28, 2021, 9:20 PM
 */


#include "xc.h"
#include <stdio.h>
#include "EE3102_Project_cbLib_v001.h"
#include "EE3102_Project_lcdLib_v001.h"
#include "EE3102_Project_genLib_v001.h"

// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)
#pragma config ICS = PGx1          // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF        // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF          // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF           // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF        // JTAG Port Enable (JTAG port is disabled)


// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config I2C1SEL = PRI       // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF       // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON       // Primary Oscillator I/O Function (CLKO/RC15 functions as I/O pin)
#pragma config FCKSM = CSECME      // Clock Switching and Monitor (Clock switching is enabled, 
                                       // Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL      // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))

#define PERIOD 5

void __attribute__((interrupt, auto_psv)) _ADC1Interrupt(void){
    _AD1IF = 0;
    
    int adValue = ADC1BUF0;
    putVal(adValue);
}

void __attribute__((__interrupt__, __auto_psv__)) _T2Interrupt(void) {
    _T2IF = 0;
    
    lcd_setCursor(0, 0);
	unsigned long data = getAvg();
    char dataStr[20]; 
    //sprintf(dataStr, "%6f", (1.0 * data)/* / 1023*/);
    double linearized = 0;
    if(data <= 909){
        linearized = (1/35.391) * (data) + 2;
    } else if(data < 1023){
        linearized = (1/3.0516) * (data) - 277;
    }
	sprintf(dataStr, "%6f mA", (1.0 * linearized));
	lcd_printStr(dataStr);
}

void setup() {
    I2C2CONbits.I2CEN = 0;
    I2C2BRG = 0x9D;
    I2C2CONbits.I2CEN = 1;
    _I2CSIDL = 0;
    IFS3bits.MI2C2IF = 0;

    initBuffer();
    lcd_init();
    lcd_setCursor(0, 0);

    AD1CON1 = 0;
    AD1CON1bits.FORM = 0; // integer
    AD1CON1bits.SSRC = 0b010; // TMR3 trigger for ADC
    AD1CON1bits.ASAM = 1; // auto sample

    AD1CON2 = 0;
    AD1CON2bits.CSCNA = 0; // do not scan
    AD1CON2bits.SMPI = 0;
    AD1CON2bits.BUFM = 0;
    //AD1CON2bits.VCFG = 0b0101;

    AD1CON3 = 0;
    AD1CON3bits.ADRC = 0; // system clock
    AD1CON3bits.ADCS = 1; // Tcy
    AD1CON3bits.SAMC = 0;
    AD1CON1bits.ADON = 1; // turn on

    AD1CHS = 0;
    AD1CHSbits.CH0NB = 0;
    AD1CHSbits.CH0SB = 0; // AN0
    AD1CHSbits.CH0NA = 0;
    AD1CHSbits.CH0SA = 0; // AN0

    T2CON = 0;
    TMR2 = 0;
    T2CONbits.TCKPS = 0b10;
    PR2 = 15624; // 100ms
    T2CONbits.TON = 1;

    T3CON = 0;
    TMR3 = 0;
    T3CONbits.TCKPS = 0b10; // pre 64
    //PR3 = (1 / K_CONST) / (.0000000625 * 64) - 1;
    PR3 = 500;//15624; // 16 samples per second
    T3CONbits.TON = 1;

    IEC0bits.AD1IE = 1;
    IFS0bits.AD1IF = 0;

    IEC0bits.T2IE = 1;
    IFS0bits.T2IF = 0;
}

int main(void) {
    pic24_init();
    initBuffer();
    setup();
    
    while(1){
        
    }
    return 0;
}
