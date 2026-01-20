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

namespace {
#define PERIOD_MS 2000ms
}
//pas de printf dans une interruption

int main()
{
    if(!bme.initialize())
        printf("errrrrrror");
    bme.set_sampling();

//    char add[3];
    while (1) {
        float temp = bme.temperature();
        float hum = bme.humidity();
        float press = bme.pressure();
        printf("température = %f, %f, %f \n", temp, hum, press);

        ThisThread::sleep_for(500);
    }
}
