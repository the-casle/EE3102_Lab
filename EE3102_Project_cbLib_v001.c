/*
 * File:   kasle_lab6_cbLib_v001.c
 * Author: jakaslewicz
 *
 * Created on April 28, 2021, 9:20 PM
 */


#include "EE3102_Project_cbLib_v001.h"

void initBuffer(void) {
    int i;
    for (i = 0; i < BUFFERSIZE; i++) {
        buffer[i] = 0;
    }
}

void putVal(int newVal) {
    buffer[buffInd] = newVal;
    buffInd = (buffInd + 1) % BUFFERSIZE; //circular that buffer
}

int getAvg(void) {
    unsigned long int sum = 0;
    int j = ((buffInd - 1) - SAMPLES + BUFFERSIZE) % BUFFERSIZE;
    int i;
    for (i = 0; i < SAMPLES; i++) {
        sum += buffer[j];
        j = (j + 1) % BUFFERSIZE;
    }
    return sum / SAMPLES;
}