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
Mutex mutex;



namespace {
#define PERIOD_MS 2000ms
}
void ping(){
    for(int i=0;i<100;i++){
        mutex.lock();
        printf("Ping\n");
        mutex.unlock();
    }
}
void pong(){
    for(int i=0;i<100;i++){
        mutex.lock();
        printf("Pong\n");
        mutex.unlock();
    }
}

int main()
{

    th1.start(ping);
    th2.start(pong);
    
    th1.set_priority(osPriorityAboveNormal3);
    th2.set_priority(osPriorityAboveNormal2);

    while(1){
        mutex.lock();
        printf("Alive! \n");
        myled = !myled;
        mutex.unlock();

        ThisThread::sleep_for(500);
    }    
}
