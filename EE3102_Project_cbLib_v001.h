/* 
 * File:   kasle_lab6_cbLib_v001.h
 * Author: jakaslewicz
 *
 * Created on April 28, 2021, 9:20 PM
 */

#ifndef KASLE_LAB6_CBLIB_V001_H
#define	KASLE_LAB6_CBLIB_V001_H

#include "xc.h"

#ifdef	__cplusplus
extern "C" {
#endif
    #define BUFFERSIZE 1024
    #define K_CONST 16
    #define SAMPLES 128
    volatile static int buffer[BUFFERSIZE];
    volatile static int buffInd = 0;
    
    void putVal(int);
    int getAvg(void);
    void initBuffer(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* KASLE_LAB6_CBLIB_V001_H */

