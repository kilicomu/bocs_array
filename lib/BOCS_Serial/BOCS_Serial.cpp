/****************************************************************************//*
 * @file    BOCS_Serial.cpp
 * @author  Killian Murphy <killian.murphy@york.ac.uk>
 * @date    23 November 2018
 * @brief   Thin wrapper around Arduino Serial library to provide some BOCS-
 *          specific functionality.
 ******************************************************************************/
#include "BOCS_Serial.h"
/******************************************************************************/
void serial_init(uint32_t rate) {
  Serial.begin(rate);
  while (!Serial) {}
}
/******************************************************************************/
void serial_write_power_data(float *data, uint8_t data_len) {
  uint8_t i = 0;
  for (i = 0; i < (data_len - 1); ++i) {
    Serial.print(data[i]);
    Serial.print(F(","));
  }
  Serial.print(data[i]);
}
