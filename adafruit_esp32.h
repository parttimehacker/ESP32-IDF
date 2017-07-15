/*
 * Copyright 2017 cyWren Systems, Inc. All Rights Reserved.
 * Additions Copyright 2016 Espressif Systems (Shanghai) PTE LTD
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://aws.amazon.com/apache2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

/* ESP32 IDF implementation of ADC1

typedef enum {
    ADC1_CHANNEL_0 = 0, // ADC1 channel 0 is GPIO36
    ADC1_CHANNEL_1,     // ADC1 channel 1 is GPIO37
    ADC1_CHANNEL_2,    //ADC1 channel 2 is GPIO38
    ADC1_CHANNEL_3,     //ADC1 channel 3 is GPIO39
    ADC1_CHANNEL_4,     //ADC1 channel 4 is GPIO32
    ADC1_CHANNEL_5,     // ADC1 channel 5 is GPIO33
    ADC1_CHANNEL_6,     // ADC1 channel 6 is GPIO34
    ADC1_CHANNEL_7,     //ADC1 channel 7 is GPIO35
    ADC1_CHANNEL_MAX,
} adc1_channel_t;

*/

// Adafruit's ESP32 Feather - Arduino pins

#define D12_PIN           GPIO12	// Analog A11 pull down output
#define D13_PIN           GPIO13	// Analog A12 red LED
#define D14_PIN           GPIO14  // Analog A6
#define D15_PIN           GPIO15  // Analog A8
#define D21_PIN           21
#define D27_PIN           GPIO27  // Analog A10
#define D32_PIN           GPIO32  // Analog A7  32Khz crystal
#define D33_PIN           GPIO33  // Analog A9  32Khz crystal

//#define	A0_PIN            GPIO26  // Analog     ADC and DAC
//#define	A1_PIN	          GPIO25	// Analog     ADC and DAC
//#define	A2_PIN            GPIO21	// Analog*    Analog input only
#define	A3_PIN            GPIO39	// Analog*    Analog Input Only
#define	A4_PIN	          GPIO36	// Analog		  Analog input
//#define	A5_PIN	          GPIO4   // Analog		  Analog input

#define I2C_SDA_PIN       GPIO23
#define I2C_SCL_PIN       GPIO22
