/****************************************************************************//*
 * @file    BOCS_I2C.h
 * @author  Killian Murphy <killian.murphy@york.ac.uk>
 * @date    22 November 2018
 * @brief   Usefully-named wrapper functions around Arduino Wire functions.
 ******************************************************************************/
#ifndef __BOCS_I2C_H__
#define __BOCS_I2C_H__
/******************************************************************************/
#include <Arduino.h>
#include <Wire.h>
/****************************************************************************//*
 * @brief  Configuration macros specifying I2C addresses of slave devices.
 *
 * I2C_MUX_ADDR is the I2C address of the TCA9548A.
 *
 * SENSOR_N_ADDR is the I2C address of sensors 1 through three on each of the
 * TCA9548A channels.
 ******************************************************************************/
#define I2C_MUX_ADDR 0x70
#define SENSOR_1_ADDR 0x4A
#define SENSOR_2_ADDR 0x4B
#define SENSOR_3_ADDR 0x48
/****************************************************************************//*
 * @brief  Configuration macros associating TCA9548A channel numbers with types
 *         of sensors attached.
 ******************************************************************************/
#define NO_SENSORS 0x01
#define NO2_SENSORS 0x02
#define OX_SENSORS 0x03
#define CO_SENSORS 0x04
#define CO2_SENSORS 0x05
/****************************************************************************//*
 * @brief  Initialise I2C bus, joining as master.
 ******************************************************************************/
void i2c_init_bus(void);
/****************************************************************************//*
 * @brief  Select a TCA9548A channel.
 *
 * @param[in]  channel  The channel to select, in range 0-8.
 ******************************************************************************/
uint8_t i2c_select_channel(uint8_t channel);
#endif
