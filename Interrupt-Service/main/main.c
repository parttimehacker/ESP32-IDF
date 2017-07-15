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
#include "esp_log.h"

#include "sdkconfig.h"

#include "adafruit_esp32.h"
#include "interruptService.h"

xQueueHandle gpio_evt_queue = NULL;

//////////////////////////////////////////////////////////
// Main task - read humidity and fahrenheit temperature

void main_task(void *pvParameter) {
	ESP_LOGD("main_task", "entry");

	// loop forever
	while (true) {
		uint32_t int_num;
		if ( xQueueReceive( gpio_evt_queue, &int_num, portMAX_DELAY ) ) {
    	printf("GPIO[%d] intr, val: %d\n", int_num, gpio_get_level(int_num));
    }
	}

	ESP_LOGD("main_task", "exit");
}

//////////////////////////////////////////////////////////
// app main logic

void app_main()
{
		ESP_LOGD("app_main", "initialize interrupt service");

		gpio_evt_queue = initialize_interrupt( D21_PIN, GPIO_MODE_INPUT, GPIO_PULLUP_DISABLE, GPIO_PULLDOWN_ENABLE, GPIO_INTR_POSEDGE );

		ESP_LOGD("app_main", "create and launch main_task");
		xTaskCreate(&main_task, "main_task", 2048, NULL, 5, NULL);
}
