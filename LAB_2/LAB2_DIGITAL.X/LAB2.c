/*
 * File:   LAB2.c
 * Author: Katherine Caceros
 *
 * Created on 28 de enero de 2021, 04:09 PM
 */

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#define _XTAL_FREQ  4000000

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#include <xc.h>
#include <stdint.h>
#include "Dis.h"
#include "ADC.h"

//----------------------------------------------------------------------------//
//                      Declaracion de variables                              //
//----------------------------------------------------------------------------//

int A; 
uint16_t led;   //Es un entero corto sin signo,variable en la que guardare valor 
int B;
int display1;
int display2;
int camb;
int k;


//----------------------------------------------------------------------------//
//                      Declaracion de funciones                              //
//----------------------------------------------------------------------------//
void led_cambio(void);
void compare(void);
void display(void);
void setup(void);
void ADCFULL (void);


//----------------------------------------------------------------------------//
//                              Configuracion                                 //
//----------------------------------------------------------------------------//

void main(void) {
    setup();
    FUNCION:
        led_cambio();
        ADCFULL();
        display();
        compare();
    goto FUNCION;
}


void led_cambio(void){      // aumentar o disminuer el valor de la variable A
    if (A == 1){            // si el valor de A es 1 el valor de la led aumenta
       if (led == 0){
           led = 1;
       } 
       else if (led >= 1 && led <= 255){
           led++;
       }
       else{
           led = 0;
       }
       A=0;
       PORTA = led;
    }
    else if (A == 2){       // si el vaalor de A es 2 el valor de la led decrece
        if (led == 0){
           led = 255;
       } 
       else if (led >= 1 && led <= 255){
           led--;
       }
       else{
           led = 0;
       }
       A=0;
       PORTA = led; 
    }
    else {
        A=0;
        PORTA = led;
    }
}

void display(void){     // se utilizara para colocar los valores del ADC en las variables y llamamos a la libreria
    if(B == 0){         // usara los menos significativos del ADC
        display1 = camb & 0b00001111;
        PORTDbits.RD1 = 0;
        Dis(display1);
        PORTDbits.RD2 = 1;  
    }
    else if (B == 1){   // usara los mas significativos del ADC
        display2 = camb & 0b11110000;
        display2 = display2>>4;
        PORTDbits.RD2 = 0;
        Dis(display2);
        PORTDbits.RD1 = 1;
    }
}

void compare(void){ // se compararan los valores del ADC y encendera la alarma si es necesario
    if (camb > led){
        PORTDbits.RD3 = 1;
    }
    else{
        PORTDbits.RD3 = 0;
    } 
}

void ADCFULL(void){ // solo se guarda el valor del ADC y reinicia
    if(ADCON0bits.GO_DONE == 0){ //conversion finalizada
        camb = ADRESH;
        ADCON0bits.GO_DONE = 1; // conversion en progreso 
        GO = 0;
    }
}
//----------------------------------------------------------------------------//
//                              Interrupciones                                 //
//----------------------------------------------------------------------------//

void _interrupt(); isr(void){
    if (INTCONbits.RBIF == 1){ // interrupcion del puerto B se cambia el valor de A
        if (PORTBbits.RB7 == 1){
            A = 1;
        }
        if (PORTBbits.RB3 == 0){
            A = 2;
        }
    INTCONbits.RBIF = 0;    
    }
    else if (INTCONbits.T0IF == 1){ // interrupcion del timer 0 para multiplexeado de los displays
        if(B == 1){
            B = 0;
            INTCONbits.T0IF = 0;
            TMR0 = 6;
        }
        else {
            B = 1;
            INTCONbits.T0IF = 0;
            TMR0 = 6;
        }    
    }
    else if (PIR1bits.ADIF == 1){ // interrupcion de ADC para indicar si ha terminado de convertir
        camb = ADRESH;
        ADCON0bits.GO_DONE = 1; 
        PIR1bits.ADIF = 0;
    }
}

//configuracion de puertos 

void setup(void){
    ANSEL = 0b00100000;   // se coloco como la entrada analogica del ANS para ADC
    ANSELH = 0;
    
    TRISA = 0;
    PORTA = 0;          // puertos configurados como salidas
     
    TRISC = 0;
    PORTC = 0;      
    
    TRISD= 0;
    PORTD = 0;      
    
    TRISB = 0b11111111;  // puerto B se coloco como entrada con interrupcion   
    PORTB = 0;              
    
    OPTION_REGbits.T0CS = 0; //conf del timer 0 con interrupcion de 0.0005 seg
    OPTION_REGbits.T0SE = 0;
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS2 = 0;
    OPTION_REGbits.PS1 = 0;
    OPTION_REGbits.PS0 = 0;
    TMR0 = 6;
    INTCONbits.PEIE = 1; // habilitacion perifica de interrupciones
    INTCONbits.T0IE = 1;
    INTCONbits.RBIE = 1; //bandera de interrupciones
    INTCONbits.T0IF = 0;
    INTCONbits.RBIF = 0;
    INTCONbits.GIE = 1; //habilitacion global de interrupciones
    PIE1bits.ADIE = 1; //habilita interrupcion de conversion a/d
    PIR1bits.ADIF = 0; // es una bandera de interrupcion 0 converion A/D no completada 
    ADC(); // ADC desde libreria
    led = 0;
}