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
#define MOS_BUFFER_SIZE 8
/******************************************************************************/
ADCGroup ELECTROCHEM_ADCS(3);
ADCGroup CO2_ADCS(3);
ADCGroup MOS_ADCS(4);

RTC_DS1307 rtc;

int16_t CO2_BUFFER[CO2_BUFFER_SIZE];
int16_t ELECTROCHEM_BUFFER[ELECTROCHEM_BUFFER_SIZE];
int16_t MOS_BUFFER[MOS_BUFFER_SIZE];
/***************************************************************************//**
 * @brief  Code that will run before the main execution loop.
 ******************************************************************************/
void setup() {
  serial_init(9600);
  Serial.println("INFO: INITIALISED USB SERIAL");
  
  i2c_init_bus();
  Serial.println("INFO: INITIALISED I2C BUS AND JOINED AS MASTER");

  rtc_init(rtc);
  DateTime current_time = rtc.now();
  Serial.print("INFO: INITIALISED RTC - THE TIME IS NOW ");
  Serial.print(current_time.hour());
  Serial.print(':');
  Serial.print(current_time.minute());
  Serial.print(':');
  Serial.println(current_time.second());

  i2c_select_channel(MOS_SENSORS);
  MOS_ADCS.init_all();
  Serial.println("INFO: INITIALISED MOS SENSOR ADCS");

  for (uint8_t i = NO_SENSORS; i < CO2_SENSORS; ++i) {
    i2c_select_channel(i);
    ELECTROCHEM_ADCS.init_all();
  }
  Serial.println("INFO: INITIALISED ELECTROCHEM ADCS");

  i2c_select_channel(CO2_SENSORS);
  CO2_ADCS.init_all();
  Serial.println("INFO: INITIALISED CO2 ADCS");

  i2c_select_channel(MOS_SENSORS);
  Serial.println("INFO: RESET I2C MULTIPLEXER, READY FOR SAMPLING");
}
/***************************************************************************//**
 * @brief  The main execution loop.
 ******************************************************************************/
void loop() {
  uint32_t timestamp = rtc_get_unix_time(rtc);

  Serial.print(timestamp);
  Serial.print(',');

  // READ, WRITE, AND PRINT MOS DATA:
  i2c_select_channel(MOS_SENSORS);
  Serial.println("INFO: SELECTED MOS SENSORS");
  MOS_ADCS.read_values(MOS_BUFFER);
  Serial.println("INFO: READ MOS DATA INTO BUFFER");
  serial_write_adc_group_data(MOS_BUFFER, MOS_BUFFER_SIZE);
  Serial.print("\r\n");

  // READ, WRITE, AND PRINT ELECTROCHEM DATA:
  for (uint8_t i = NO_SENSORS; i < CO2_SENSORS; ++i) {
    i2c_select_channel(i);
    Serial.println("INFO: SELECTED ELECTROCHEM ADC GROUP");
    ELECTROCHEM_ADCS.read_values(ELECTROCHEM_BUFFER);
    Serial.println("INFO: READ ELECTROCHEM DATA INTO BUFFER");
    serial_write_adc_group_data(ELECTROCHEM_BUFFER, ELECTROCHEM_BUFFER_SIZE);
  }

  // READ, WRITE, AND PRINT CO2 DATA:
  i2c_select_channel(CO2_SENSORS);
  Serial.println("INFO: SELECTED CO2 ADC GROUP");
  CO2_ADCS.read_values(CO2_BUFFER);
  Serial.println("INFO: READ CO2 DATA INTO BUFFER");
  serial_write_adc_group_data(CO2_BUFFER, CO2_BUFFER_SIZE);
  Serial.print("\r\n");

  delay(1000);
}
