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


#include "interruptService.h"

//////////////////////////////////////////////////////////
// local data structures

static xQueueHandle gpio_evt_queue = NULL;

//////////////////////////////////////////////////////////
// declare the interrupt handler

static void IRAM_ATTR gpio_isr_handler(void* arg)
{
    uint32_t gpio_num = (uint32_t) arg;
    xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
}

//////////////////////////////////////////////////////////
// configure an interrupt handler

xQueueHandle initialize_interrupt(
  uint32_t gpio_pin,
  gpio_mode_t int_mode,
  gpio_pullup_t pull_up,
  gpio_pulldown_t pull_down,
  gpio_int_type_t int_type ) {

  // set up the interrupt configuration

  gpio_config_t io_conf;
  io_conf.pin_bit_mask = 1 << gpio_pin ;
  io_conf.mode = int_mode;
  io_conf.pull_up_en = pull_up;
  io_conf.pull_down_en = pull_down;
  io_conf.intr_type = int_type;
  gpio_config(&io_conf);

  //create a queue to handle gpio event from isr
  gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));

  //install gpio isr service
  gpio_install_isr_service(ESP_INTR_FLAG_SHARED);

  //hook isr handler for specific gpio pin
  gpio_isr_handler_add(gpio_pin, gpio_isr_handler, (void*) gpio_pin);
  //hook isr handler for specific gpio pin

  return gpio_evt_queue;
}
