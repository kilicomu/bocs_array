/***************************************************************************//**
 * @file    main.cpp
 * @author  Killian Murphy <killian.murphy@york.ac.uk>
 * @date    21 November 2018
 * @brief   Read data from attached sensors and send over USB serial.
 ******************************************************************************/
#include <Arduino.h>
#include <BOCS_ADC.h>
#include <BOCS_I2C.h>
#include <BOCS_SD.h>
#include <BOCS_Serial.h>
/******************************************************************************/
ADCGroup electrochem_adcs;
ADCGroup co2_adcs;
int16_t adc_value_buffer[ADC_VALUE_BUFFER_LENGTH];
File data_file;
/***************************************************************************//**
 * @brief  Code that will run before the main execution loop.
 ******************************************************************************/
void setup() {
  serial_init(BAUD_RATE);
  Serial.println("INFO: INITIALISED USB SERIAL");

  i2c_init_bus();
  Serial.println("INFO: INITIALISED I2C BUS; JOINED AS MASTER");

  sd_init();
  Serial.println("INFO: INITIALISED SD CARD DEVICE");

  electrochem_adcs.init_all();
  Serial.println("INFO: INITIALISED ELECTROCHEM ADCS");

  co2_adcs.init_all();
  Serial.println("INFO: INITIALISED CO2_ADCS");
}
/***************************************************************************//**
 * @brief  The main execution loop.
 ******************************************************************************/
void loop() {
  i2c_select_channel(NO_SENSORS);

  electrochem_adcs.read_values(adc_value_buffer);

  serial_write_adc_group_data(adc_value_buffer, ADC_VALUE_BUFFER_LENGTH);
  Serial.print("\r\n");

  data_file = SD.open(DATA_FILE_NAME, FILE_WRITE);
  if (data_file) {
    sd_write_adc_group_data(data_file, adc_value_buffer, ADC_VALUE_BUFFER_LENGTH);
    data_file.print("\r\n");
    data_file.close();
  } else {
    Serial.println("ERROR: UNABLE TO OPEN DATA FILE FOR WRITING");
  }

  delay(1000);
}
