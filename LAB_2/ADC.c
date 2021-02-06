/*
 * File:   ADC.c
 * Author: Katherine Caceros
 *
 * Created on 28 de enero de 2021, 09:30 PM
 */


#include "ADC.h"

void ADC(void) {
    ADCON1 = 0;
    ADCON0 = 0b01010101;
    ADCON0bits.GO_DONE = 1;
    return;
}
