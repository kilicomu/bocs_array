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
ADCGroup ELECTROCHEM_ADCS(3);
ADCGroup CO2_ADCS(3);
ADCGroup MOS_ADCS(4);

RTC_DS1307 rtc;
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

  sd_init();
  Serial.println("INFO: INITIALISED SD CARD");

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
}
/***************************************************************************//**
 * @brief  The main execution loop.
 ******************************************************************************/
void loop() {

}
