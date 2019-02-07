/****************************************************************************//*
 * @file    BOCS_SD.cpp
 * @author  Killian Murphy <killian.murphy@york.ac.uk>
 * @date    23 November 2018
 * @brief   Thin wrappers around Arduino SD library functions.
 ******************************************************************************/
#include "BOCS_SD.h"
/******************************************************************************/
void sd_init(void) {
  if (!SD.begin()) {
    Serial.println(F("ERROR: UNABLE TO INITIALISE SD CARD CAPABILITY"));
    while(1);
  }
}
/******************************************************************************/
void sd_write_power_data(File file, float *data, uint8_t data_len) {
  uint8_t i;
  for (i = 0; i < (data_len - 1); ++i) {
    file.print(data[i]);
    file.print(',');
  }
  file.print(data[i]);
}
