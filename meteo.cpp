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
int flag =0;


namespace {
#define PERIOD_MS 2000ms
}
void temp(){
    while(1){
        mutex.lock();
        float temp = bme.temperature();
        float hum = bme.humidity();
        printf("temperature = %2.2f°C, humidity = %2.2f% \n", temp, hum);
        mutex.unlock();
        ThisThread::sleep_for(2000);
    }
}
void press(){
    flag = 1;
}

void led(){
    while(1){
    myled = !myled;
    ThisThread::sleep_for(5000);
    }
}

int main()
{
    if(!bme.initialize())
        printf("errrrrrror");
    bme.set_sampling();

    th1.start(temp);
    th2.start(led);

    th1.set_priority(osPriorityAboveNormal3);
    th2.set_priority(osPriorityAboveNormal3);

    button.rise(&press);

    while(1){
        if(flag){
            float press = bme.pressure();
            printf("pressure = %2.2f HPa\n",press/100);
            flag=0;
        }
        ThisThread::sleep_for(100);
    }    
}
