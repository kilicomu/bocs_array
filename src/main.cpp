/***************************************************************************//**
 * @file    main.cpp
 * @author  Killian Murphy <killian.murphy@york.ac.uk>
 * @date    21 November 2018
 * @brief   Read data from attached sensors and send over USB serial.
 ******************************************************************************/
#include <Arduino.h>
#include <BOCS_ADC.h>
#include <BOCS_I2C.h>
/******************************************************************************/
ADCGroup adcs;
int16_t adc_values[3];
/***************************************************************************//**
 * @brief  Code that will run before the main execution loop.
 ******************************************************************************/
void setup() {
  Serial.begin(9600);
  while (!Serial) {}
  Serial.println("INFO: SERIAL INITIALISED");

  i2c_init_bus();
  Serial.println("INFO: JOINED I2C BUS AS MASTER");

  adcs.adc_init_all();
  Serial.println("INFO: INITIALISED ADCS");
}
/***************************************************************************//**
 * @brief  The main execution loop.
 ******************************************************************************/
void loop() {
  i2c_select_channel(NO_SENSORS);
  adcs.read_values(adc_values);
  Serial.print(adc_values[0]);
  Serial.print(",");
  Serial.print(adc_values[1]);
  Serial.print(",");
  Serial.println(adc_values[2]);
  i2c_select_channel(NO2_SENSORS);
  adcs.read_values(adc_values);
  Serial.print(adc_values[0]);
  Serial.print(",");
  Serial.print(adc_values[1]);
  Serial.print(",");
  Serial.println(adc_values[2]);
  delay(1000);
}
