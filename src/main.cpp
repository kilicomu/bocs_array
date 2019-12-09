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
#define POWER_BUFFER_SIZE 3
/******************************************************************************/
ADCGroup ELECTROCHEM_ADCS(3);
ADCGroup CO2_ADCS(3);
ADCGroup MOS_ADCS(4);
ADCGroup META_ADCS(2);

Adafruit_INA219 POWER_SENSOR;
Adafruit_INA219 POWER_SENSOR_2(0x41);
RTC_DS1307 rtc;

float POWER_BUFFER[POWER_BUFFER_SIZE];

char FILENAME[12] = {'\0'};
File DATA_FILE;
/*****************************************************************************
 * @brief  Sample a group of ADCs, write the recorded values to USB serial and
 *         SD.
 *
 * @param[in]     adc_channel     The TCA channel of the ADCs to be sampled.
 * @param[inout]  adc_group       The ADCGroup object corresponding to the ADCs
 *                                to be sampled.
 * @param[inout]  data_file       The SD data file to be written to.
 * @param[in]     trailing_comma  Whether or not to write a trailing comma to
 *                                output streams.
 * 
 ******************************************************************************/
void sample_adc_group(uint8_t adc_channel, ADCGroup adc_group,
                      File data_file, uint8_t trailing_comma) {
  i2c_select_channel(adc_channel);

  i2c_read_channel_power(POWER_SENSOR, POWER_BUFFER);
  serial_write_power_data(POWER_BUFFER, POWER_BUFFER_SIZE);
  sd_write_power_data(data_file, POWER_BUFFER, POWER_BUFFER_SIZE);
  Serial.print(F(","));
  data_file.print(F(","));

  if (adc_channel == 0) {
    i2c_read_channel_power(POWER_SENSOR_2, POWER_BUFFER);
    serial_write_power_data(POWER_BUFFER, POWER_BUFFER_SIZE);
    sd_write_power_data(data_file, POWER_BUFFER, POWER_BUFFER_SIZE);
    Serial.print(F(","));
    data_file.print(F(","));
  }
  
  adc_group.read_values();
  adc_group.write_values_to_serial();
  adc_group.write_values_to_sd(data_file);
  
  if (trailing_comma) {
    Serial.print(F(","));
    data_file.print(F(","));
  }
}
/*****************************************************************************
 * @brief  Code that will run before the main execution loop.
 ******************************************************************************/
void setup() {
  serial_init(BAUD_RATE);
  i2c_init_bus();
  rtc_init(rtc);
  sd_init();

  i2c_select_channel(MOS_SENSORS);
  POWER_SENSOR.begin();
  POWER_SENSOR_2.begin();
  MOS_ADCS.init_all();

  for (uint8_t i = NO_SENSORS; i < CO2_SENSORS; ++i) {
    i2c_select_channel(i);
    POWER_SENSOR.begin();
    ELECTROCHEM_ADCS.init_all();
  }

  i2c_select_channel(CO2_SENSORS);
  POWER_SENSOR.begin();
  CO2_ADCS.init_all();

  i2c_select_channel(PUMP_SENSORS);
  POWER_SENSOR.begin();

  i2c_select_channel(META_SENSORS);
  META_ADCS.init_all();
}
/*****************************************************************************
 * @brief  The main execution loop.
 ******************************************************************************/
void loop() {
  DateTime iter_start_dt = rtc.now();

  // GET CURRENT DAY AND PRINT INTO DATA FILE NAME, CONFIRMING THAT WE CAN OPEN
  // THE DATA FILE ON THE SD CARD:
  sprintf(FILENAME, "%04d%02d%02d.CSV", iter_start_dt.year(),
          iter_start_dt.month(), iter_start_dt.day());
  DATA_FILE = SD.open(FILENAME, FILE_WRITE);
  if (! DATA_FILE) {
    Serial.println("ERROR: UNABLE TO OPEN SD CARD FILE");
  }
  
  // PRINT UNIX TIMESTAMP AS FIRST FIELD OF DATA:
  uint32_t timestamp = iter_start_dt.unixtime();
  Serial.print(timestamp);
  Serial.print(F(","));
  DATA_FILE.print(timestamp);
  DATA_FILE.print(",");
 
  // SAMPLE DATA FROM POWER SENSORS & ADCS AND WRITE TO USB SERIAL/SD CARD:
  sample_adc_group(MOS_SENSORS, MOS_ADCS, DATA_FILE, 1);
  sample_adc_group(NO_SENSORS, ELECTROCHEM_ADCS, DATA_FILE, 1); 
  sample_adc_group(CO_SENSORS, ELECTROCHEM_ADCS, DATA_FILE, 1);
  sample_adc_group(OX_SENSORS, ELECTROCHEM_ADCS, DATA_FILE, 1);
  sample_adc_group(NO2_SENSORS, ELECTROCHEM_ADCS, DATA_FILE, 1);
  sample_adc_group(CO2_SENSORS, CO2_ADCS, DATA_FILE, 1);
 
  // SAMPLE PUMP POWER DATA AND WRITE TO USB SERIAL/SD CARD:
  i2c_select_channel(PUMP_SENSORS);
  i2c_read_channel_power(POWER_SENSOR, POWER_BUFFER);
  serial_write_power_data(POWER_BUFFER, POWER_BUFFER_SIZE);
  sd_write_power_data(DATA_FILE, POWER_BUFFER, POWER_BUFFER_SIZE);
  Serial.print(F(","));
  DATA_FILE.print(",");

  // SAMPLE META SENSORS AND WRITE TO USB SERIAL/SD CARD:
  i2c_select_channel(META_SENSORS);
  META_ADCS.read_values_nd();
  META_ADCS.write_u_values_to_serial();
  META_ADCS.write_u_values_to_sd(DATA_FILE);

  // WRITE NEW LINE TO USB SERIAL/SD CARD:
  Serial.print(F("\r\n"));
  DATA_FILE.print("\r\n");

  // FLUSH THE SD CARD WRITE BUFFER:
  DATA_FILE.close();

  while((rtc.now() - iter_start_dt).totalseconds() < 2) {}
}
