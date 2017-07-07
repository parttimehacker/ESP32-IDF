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

#ifndef _DRIVER_SI7021_H_
#define _DRIVER_SI7021_H_
#include <driver/i2c.h>
#endif

// I2C address for Silicon Labs I2C Humidity and tempeature sensor
#define SI7021_DEFAULT_ADDRESS         (0x40)

// device commands
#define SI7021_MEASRH_HOLD_CMD           0xE5
#define SI7021_MEASRH_NOHOLD_CMD         0xF5
#define SI7021_MEASTEMP_HOLD_CMD         0xE3
#define SI7021_MEASTEMP_NOHOLD_CMD       0xF3
#define SI7021_READPREVTEMP_CMD          0xE0
#define SI7021_RESET_CMD                 0xFE
#define SI7021_WRITERHT_REG_CMD          0xE6
#define SI7021_READRHT_REG_CMD           0xE7
#define SI7021_WRITEHEATER_REG_CMD       0x51
#define SI7021_READHEATER_REG_CMD        0x11
#define SI7021_ID1_CMD                   0xFA0F
#define SI7021_ID2_CMD                   0xFCC9
#define SI7021_FIRMVERS_CMD              0x84B8

// I2C helper defines
#define WRITE_BIT  I2C_MASTER_WRITE // I2C master write
#define READ_BIT   I2C_MASTER_READ  // I2C master read
#define ACK_CHECK_EN   0x1          // I2C master will check ack from slave
#define ACK_CHECK_DIS  0x0          //I2C master will not check ack from slave
#define ACK_VAL    0x0              //I2C ack value
#define NACK_VAL   0x1              //I2C nack value

// selection for temperature type
#define CELSIUS      0
#define FAHRENHEIT   1

//////////////////////////////////////////////////////////
// initialize the SI7021 device
void si2071_init( i2c_port_t i2c_port, uint8_t i2c_Address );

//////////////////////////////////////////////////////////
// reset the SI7021
void si7021_reset();

//////////////////////////////////////////////////////////
// get the current humidity
float si7021_read_humidity( void );

//////////////////////////////////////////////////////////
// get the current temperature (C or F)
float si7021_read_temperature( int mode );
