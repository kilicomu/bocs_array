/****************************************************************************//*
 * @file    BOCS_I2C.cpp
 * @author  Killian Murphy <killian.murphy@york.ac.uk>
 * @date    22 November 2018
 * @brief   Usefully-named wrapper functions around Arduino Wire functions.
 ******************************************************************************/
#include "BOCS_I2C.h"
/******************************************************************************/
void i2c_init_bus(void) {
  Wire.begin();
}
/******************************************************************************/
uint8_t i2c_select_channel(uint8_t channel) {
  Wire.beginTransmission(I2C_MUX_ADDR);
  Wire.write(1 << channel);
  return Wire.endTransmission();
}
/******************************************************************************/
