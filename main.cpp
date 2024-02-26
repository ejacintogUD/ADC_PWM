/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */


#include "BufferedSerial.h"
#include "mbed.h"

#define SAMPLE_TIME 500ms

Thread hilo_leer_adc;

void leer_adc(void);

BufferedSerial pc(USBTX, USBRX);

// pines y puertos a usar
AnalogIn Vin (A0);
PwmOut   Vel_motor (D7);


//variables globales
float voltaje=0.0;
float vel_interna=0.0;
int entera=0;
int decimal=0;
char men[30];
char ancho_char[4];
float ancho_f;


int main()
{
    // Initialise the digital pin LED1 as an output
    PwmOut led(LED1);
    Vel_motor.period_us(833);
    hilo_leer_adc.start(leer_adc);
    while (true) {
       
        vel_interna += 0.1;
        if (vel_interna > 0.9) vel_interna=0.0;
        Vel_motor = vel_interna;
        led = vel_interna;
        ThisThread::sleep_for(SAMPLE_TIME);
    }
}

void leer_adc(void)
{

    while(true)
    {
        voltaje = Vin;
            
        voltaje = voltaje*3.3;
        entera = int(voltaje);
        decimal = int((voltaje-entera)*1000);
        sprintf(men, "El voltaje es: %u.%03u \n\r", entera, decimal);
        pc.write(men,sizeof(men) );
        ThisThread::sleep_for(SAMPLE_TIME);

    }

}


