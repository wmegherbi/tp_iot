/*
 * Copyright (c) 2022, CATIE
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include "bme280.h"
using namespace sixtron;
DigitalOut myled(LED1);
InterruptIn button(BUTTON1);
I2C i2c(I2C1_SDA, I2C1_SCL);
BME280 bme(&i2c);
bme280_environment_t env;
Thread th1;
Thread th2;

namespace {
#define PERIOD_MS 2000ms
}
//pas de printf dans une interruption
void ping(){
    for(int i=0;i<100;i++){
        printf("Ping\n");
    }
}
void pong(){
    for(int i=0;i<100;i++){
        printf("Pong\n");
    }
}

int main()
{
   
    th1.start(ping);
    th2.start(pong);

    while(1){
        printf("Alive! \n");
        myled = !myled;
        ThisThread::sleep_for(500);
    }    
}
