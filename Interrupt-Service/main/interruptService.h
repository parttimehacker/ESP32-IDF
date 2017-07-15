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

#ifndef _INTERRUPT_SERVICE_PTH_H_
#define _INTERRUPT_SERVICE_PTH_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "adafruit_esp32.h"
#endif

// set up an interrupt handler and return queue

xQueueHandle initialize_interrupt(
  uint32_t gpio_pin,
  gpio_mode_t int_mode,
  gpio_pullup_t pull_up,
  gpio_pulldown_t pull_down,
  gpio_int_type_t int_type );
