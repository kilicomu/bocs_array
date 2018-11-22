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
ADCGroup electrochem_adcs;
ADCGroup co2_adcs;
int16_t adc_value_buffer[ADC_VALUE_BUFFER_LENGTH];
/***************************************************************************//**
 * @brief  Code that will run before the main execution loop.
 ******************************************************************************/
void setup() {
  Serial.begin(9600);
  while (!Serial) {}
  Serial.println("INFO: INITIALISED USB SERIAL");

  i2c_init_bus();
  Serial.println("INFO: INITIALISED I2C BUS; JOINED AS MASTER");

  electrochem_adcs.init_all();
  Serial.println("INFO: INITIALISED ELECTROCHEM ADCS");

  co2_adcs.init_all();
  Serial.println("INFO: INITIALISED CO2_ADCS");
}
/***************************************************************************//**
 * @brief  The main execution loop.
 ******************************************************************************/
void loop() {
  Serial.println("INFO: READING NO SENSORS");
  i2c_select_channel(NO_SENSORS);
  electrochem_adcs.read_values(adc_value_buffer);
  for (uint8_t i = 0; i < ADC_VALUE_BUFFER_LENGTH; ++i) {
    Serial.println(adc_value_buffer[i]);
  }

  Serial.println("INFO: READING NO2_SENSORS");
  i2c_select_channel(NO2_SENSORS);
  electrochem_adcs.read_values(adc_value_buffer);
  for (uint8_t i = 0; i < ADC_VALUE_BUFFER_LENGTH; ++i) {
    Serial.println(adc_value_buffer[i]);
  }

  delay(1000);
}
