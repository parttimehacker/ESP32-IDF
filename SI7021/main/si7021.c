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

#include "si7021.h"

// locally declared values used by I2C functions
static i2c_port_t _i2c_port = 0;
static uint8_t _si7021_address = SI7021_DEFAULT_ADDRESS;

//////////////////////////////////////////////////////////
// initialize the device

void si2071_init( i2c_port_t i2c_port, uint8_t i2c_Address ) {
  _i2c_port = i2c_port;
  _si7021_address = i2c_Address;
}

//////////////////////////////////////////////////////////
// reset the device

void si7021_reset() {
  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, _si7021_address << 1 | WRITE_BIT, ACK_CHECK_EN);
  i2c_master_write_byte(cmd, (uint8_t)SI7021_RESET_CMD, ACK_CHECK_EN);
  i2c_master_stop(cmd);
  int ret = i2c_master_cmd_begin(_i2c_port, cmd, 1000 / portTICK_RATE_MS);
  i2c_cmd_link_delete(cmd);
  if (ret == ESP_FAIL) {
    return;
  }
  vTaskDelay(30 / portTICK_RATE_MS);
}

//////////////////////////////////////////////////////////
// read humidity

float si7021_read_humidity(void) {

  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, _si7021_address << 1 | WRITE_BIT, ACK_CHECK_EN);
  i2c_master_write_byte(cmd, SI7021_MEASRH_NOHOLD_CMD, ACK_CHECK_EN);
  i2c_master_stop(cmd);
  int ret = i2c_master_cmd_begin(_i2c_port, cmd, 1000 / portTICK_RATE_MS);
  i2c_cmd_link_delete(cmd);
  if (ret == ESP_FAIL) {
    return ret;
  }
  vTaskDelay(25 / portTICK_RATE_MS);

  uint8_t data_h;
  uint8_t data_l;
  uint8_t chksum;

  cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, _si7021_address << 1 | READ_BIT, ACK_CHECK_EN);
  i2c_master_read_byte(cmd, &data_h, ACK_VAL);
  i2c_master_read_byte(cmd, &data_l, ACK_VAL);
  i2c_master_read_byte(cmd, &chksum, NACK_VAL);
  i2c_master_stop(cmd);
  ret = i2c_master_cmd_begin(_i2c_port, cmd, 1000 / portTICK_RATE_MS);
  i2c_cmd_link_delete(cmd);
  if (ret == ESP_FAIL) {
    return ret;
  }

  uint16_t data_w = data_h << 8;
  data_w |= data_l;

  float humidity = data_w;
  humidity *= 125;
  humidity /= 65536;
  humidity -= 6;

  return humidity;
}

//////////////////////////////////////////////////////////
// read temperature

float si7021_read_temperature( int mode ) {
  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, _si7021_address << 1 | WRITE_BIT, ACK_CHECK_EN);
  i2c_master_write_byte(cmd, SI7021_MEASTEMP_NOHOLD_CMD, ACK_CHECK_EN);
  i2c_master_stop(cmd);
  int ret = i2c_master_cmd_begin(_i2c_port, cmd, 1000 / portTICK_RATE_MS);
  i2c_cmd_link_delete(cmd);
  if (ret == ESP_FAIL) {
    return ret;
  }
  vTaskDelay(25 / portTICK_RATE_MS);

  uint8_t data_h;
  uint8_t data_l;
  uint8_t chksum;

  cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, _si7021_address << 1 | READ_BIT, ACK_CHECK_EN);
  i2c_master_read_byte(cmd, &data_h, ACK_VAL);
  i2c_master_read_byte(cmd, &data_l, ACK_VAL);
  i2c_master_read_byte(cmd, &chksum, NACK_VAL);
  i2c_master_stop(cmd);
  ret = i2c_master_cmd_begin(_i2c_port, cmd, 1000 / portTICK_RATE_MS);
  i2c_cmd_link_delete(cmd);
  if (ret == ESP_FAIL) {
    return ret;
  }

  uint16_t data_w = data_h << 8;
  data_w |= data_l;

  float celsius = data_w;
  celsius *= 175.72;
  celsius /= 65536;
  celsius -= 46.85;

  if (mode == CELSIUS) {
    return celsius;
  }

  return (float)((celsius * (9.0/5.0) ) + 32.0);

}
