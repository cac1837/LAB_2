/*
 * File:   Dis.c
 * Author: Katherine Caceros
 *
 * Created on 29 de enero de 2021, 06:20 PM
 */


#include "Dis.h"
int k;
void Dis(int k) {
    switch(k){
        case (0):
            PORTC = 0x77; //119
            break;
        case (1):
            PORTC = 0x14; //20
            break;
        case (2):
            PORTC = 0xB3; //179
            break;
        case (3):
            PORTC = 0xB6; //182
            break;
        case (4):
            PORTC = 0xD4; //212
            break;
        case (5):
            PORTC = 0xE6; //230
            break;
        case (6):
            PORTC = 0xE7; //231
            break;
        case (7):
            PORTC = 0x34; //52
            break;
        case (8):
            PORTC = 0xF7; //247
            break;
        case (9):
            PORTC = 0xF4; //244
            break;
        case (10):
            PORTC = 0xF5; //245
            break;
        case (11):
            PORTC = 0xC7; //199
            break;
        case (12):
            PORTC = 0x63; //99
            break;
        case (13):
            PORTC = 0x97; //151
            break;
        case (14):
            PORTC = 0xE3; //227
            break;
        case (15):
            PORTC = 0xE1; //225
            break;
        case (16):
            PORTC = 0;
            break;
    }
}
