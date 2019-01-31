/***************************************************************************//**
 * @file    main.cpp
 * @author  Killian Murphy <killian.murphy@york.ac.uk>
 * @date    21 November 2018
 * @brief   Read data from attached sensors and send over USB serial.
 ******************************************************************************/
#include <Arduino.h>
#include <BOCS_ADC.h>
#include <BOCS_I2C.h>
#include <BOCS_RTC.h>
#include <BOCS_SD.h>
#include <BOCS_Serial.h>
/******************************************************************************/
#define CO2_BUFFER_SIZE 6
#define ELECTROCHEM_BUFFER_SIZE 6
#define META_BUFFER_SIZE 4
#define MOS_BUFFER_SIZE 8
/******************************************************************************/
ADCGroup ELECTROCHEM_ADCS(3);
ADCGroup CO2_ADCS(3);
ADCGroup MOS_ADCS(4);
ADCGroup META_ADCS(2);

RTC_DS1307 rtc;

int16_t CO2_BUFFER[CO2_BUFFER_SIZE];
int16_t ELECTROCHEM_BUFFER[ELECTROCHEM_BUFFER_SIZE];
int16_t MOS_BUFFER[MOS_BUFFER_SIZE];
int16_t META_BUFFER[META_BUFFER_SIZE];
/***************************************************************************//**
 * @brief  Code that will run before the main execution loop.
 ******************************************************************************/
void setup() {
  serial_init(9600);
  i2c_init_bus();
  rtc_init(rtc);
  i2c_select_channel(MOS_SENSORS);
  MOS_ADCS.init_all();
  for (uint8_t i = NO_SENSORS; i < CO2_SENSORS; ++i) {
    i2c_select_channel(i);
    ELECTROCHEM_ADCS.init_all();
  }
  i2c_select_channel(CO2_SENSORS);
  CO2_ADCS.init_all();
  i2c_select_channel(META_SENSORS);
  META_ADCS.init_all();
  i2c_select_channel(MOS_SENSORS);
}
/***************************************************************************//**
 * @brief  The main execution loop.
 ******************************************************************************/
void loop() {
  uint32_t timestamp = rtc_get_unix_time(rtc);
  Serial.print(timestamp);
  Serial.print(F(","));
  
  i2c_select_channel(MOS_SENSORS);
  MOS_ADCS.read_values(MOS_BUFFER);
  serial_write_adc_group_data(MOS_BUFFER, MOS_BUFFER_SIZE);
  Serial.print(F(","));
 
  i2c_select_channel(NO_SENSORS);
  ELECTROCHEM_ADCS.read_values(ELECTROCHEM_BUFFER);
  serial_write_adc_group_data(ELECTROCHEM_BUFFER, ELECTROCHEM_BUFFER_SIZE);
  Serial.print(F(","));
  
  i2c_select_channel(CO_SENSORS);
  ELECTROCHEM_ADCS.read_values(ELECTROCHEM_BUFFER);
  serial_write_adc_group_data(ELECTROCHEM_BUFFER, ELECTROCHEM_BUFFER_SIZE);
  Serial.print(F(","));

  i2c_select_channel(OX_SENSORS);
  ELECTROCHEM_ADCS.read_values(ELECTROCHEM_BUFFER);
  serial_write_adc_group_data(ELECTROCHEM_BUFFER, ELECTROCHEM_BUFFER_SIZE);
  Serial.print(F(","));

  i2c_select_channel(NO2_SENSORS);
  ELECTROCHEM_ADCS.read_values(ELECTROCHEM_BUFFER);
  serial_write_adc_group_data(ELECTROCHEM_BUFFER, ELECTROCHEM_BUFFER_SIZE);
  Serial.print(F(","));
  
  i2c_select_channel(CO2_SENSORS);
  CO2_ADCS.read_values(CO2_BUFFER);
  serial_write_adc_group_data(CO2_BUFFER, CO2_BUFFER_SIZE);

  i2c_select_channel(META_SENSORS);
  META_ADCS.read_values_nd(META_BUFFER);
  serial_write_adc_group_data(META_BUFFER, META_BUFFER_SIZE);

  Serial.print(F("\r\n"));
  
  delay(1000);
}
