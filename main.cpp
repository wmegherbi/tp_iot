/*
 * Copyright (c) 2022, CATIE
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
DigitalOut myled(LED1);
InterruptIn button(BUTTON1);
Timer t;
int flag = 0;
namespace {
#define PERIOD_MS 2000ms
}
//pas de printf dans une interruption
void on(){
    myled = 1;
    t.start();
}

void off(){
    t.stop();
    myled = 0;
    flag = 1;
}
int main()
{
    myled = 0;
    button.rise(&on);
    button.fall(&off);
    while (1) {
        if(flag){
            printf("Durée de l'appui : %d us \n",t.elapsed_time());
            flag = 0;
            t.reset();

        }
        ThisThread::sleep_for(200);
    }
}
