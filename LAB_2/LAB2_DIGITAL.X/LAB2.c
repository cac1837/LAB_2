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

#define _XTAL_FREQ  8000000

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#include <xc.h>
//----------------------------------------------------------------------------//
//                      Declaracion de variables                              //
//----------------------------------------------------------------------------//

int A = 0; 
unsigned short int led; //Es un entero corto sin signo,


//----------------------------------------------------------------------------//
//                      Declaracion de funciones                              //
//----------------------------------------------------------------------------//
void led_cambio(void);
void comparar(void);
void display(void);


//----------------------------------------------------------------------------//
//                              Configuracion                                 //
//----------------------------------------------------------------------------//

void main(void) {
    if (A == 1){ // si el valor de A es 1 el valor de la led aumenta
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
    else if (A == 2){ // si el vaalor de A es 2 el valor de la led decrece
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

void display(void){ // se utilizara para colocar los valores del ADC en las variables y llamamos a la libreria
    if(B == 0){ // usara los mas significativos del ADC
        display_1 = 
        
    }
}



void setup(void){
    ANSEL = 0;        // Establecemos los puertos
    ANSELH = 0;
    
    PORTA = 0;
    
    TRISE = 0;      //Establecemos el puerto E como salida y se limpia
    PORTE = 0;      //SEMAFORO
    
    TRISC = 0;
    PORTC = 0;      //JUGADOR 1
    
    TRISD= 0;
    PORTD = 0;      //JUGAROR 2
    
    TRISB = 0B00001111;     
    PORTB = 0;              // BOTONES DE JUGADOR Y RST
    
  
}

void led_cambio(void){ // aumentar o disminuer el valor de la variable A
    
}