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
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_log.h"

#include <driver/i2c.h>
#include "sdkconfig.h"

#include "si7021.h"


//////////////////////////////////////////////////////////
// I2C port 0 master initialization

static void i2c_master_init() {
	ESP_LOGD("i2c_master_init", "entry");
	int i2c_master_port =   I2C_NUM_0;

	i2c_config_t conf;
	conf.mode =             I2C_MODE_MASTER;
	conf.sda_io_num =       CONFIG_ADAFRUIT_SDA_PIN;
	conf.sda_pullup_en =    GPIO_PULLUP_ENABLE;
	conf.scl_io_num =       CONFIG_ADAFRUIT_SCL_PIN;
	conf.scl_pullup_en =    GPIO_PULLUP_ENABLE;
	conf.master.clk_speed = 100000;

	ESP_LOGD("i2c_master_init", "setting param config");
	i2c_param_config(i2c_master_port, &conf);

	ESP_LOGD("i2c_master_init", "installing driver");
	i2c_driver_install(i2c_master_port, conf.mode, 0, 0, 0);

	ESP_LOGD("i2c_master_init", "exit");
}

//////////////////////////////////////////////////////////
// Main task - read humidity and fahrenheit temperature

void main_task(void *pvParameter) {
	ESP_LOGD("main_task", "entry");

	while (true) {

		float humidity = si7021_read_humidity();
		printf("SI7021 humidity = %5.2f",humidity);

		float fahrenheit = si7021_read_temperature(FAHRENHEIT);
		printf("\t%5.2f F\n",fahrenheit);

		vTaskDelay(5000 / portTICK_RATE_MS);
	}
}

//////////////////////////////////////////////////////////
// app main logic

void app_main()
{
		ESP_LOGD("app_main", "initialize I2C port 0 master");
		i2c_master_init();

		ESP_LOGD("app_main", "initialize SI7020 sensor");
		si2071_init((i2c_port_t)I2C_NUM_0, (uint8_t)SI7021_DEFAULT_ADDRESS);

		ESP_LOGD("app_main", "create and launch main_task");
		xTaskCreate(&main_task, "main_task", 2048, NULL, 5, NULL);
}
