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
#define POWER_BUFFER_SIZE 3
/******************************************************************************/
ADCGroup ELECTROCHEM_ADCS(3);
ADCGroup CO2_ADCS(3);
ADCGroup MOS_ADCS(4);
ADCGroup META_ADCS(2);

Adafruit_INA219 POWER_SENSOR;
RTC_DS1307 rtc;

int16_t CO2_BUFFER[CO2_BUFFER_SIZE];
int16_t ELECTROCHEM_BUFFER[ELECTROCHEM_BUFFER_SIZE];
int16_t MOS_BUFFER[MOS_BUFFER_SIZE];
int16_t META_BUFFER[META_BUFFER_SIZE];
float POWER_BUFFER[POWER_BUFFER_SIZE];

char FILENAME[12] = {'\0'};
File DATA_FILE;
/***************************************************************************//**
 * @brief  Code that will run before the main execution loop.
 ******************************************************************************/
void setup() {
  serial_init(9600);
  i2c_init_bus();
  rtc_init(rtc);
  sd_init();

  i2c_select_channel(MOS_SENSORS);
  POWER_SENSOR.begin();
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
  i2c_select_channel(MOS_SENSORS);
}
/***************************************************************************//**
 * @brief  The main execution loop.
 ******************************************************************************/
void loop() {
  DateTime now = rtc.now();

  sprintf(FILENAME, "%04d%02d%02d.CSV", now.year(), now.month(), now.day());
  DATA_FILE = SD.open(FILENAME, FILE_WRITE);
  if (! DATA_FILE) {
    Serial.println("ERROR: UNABLE TO OPEN SD CARD FILE");
  }

  uint32_t timestamp = now.unixtime();
  Serial.print(timestamp);
  Serial.print(F(","));
  DATA_FILE.print(timestamp);
  DATA_FILE.print(",");
  
  i2c_select_channel(MOS_SENSORS);
  i2c_read_channel_power(POWER_SENSOR, POWER_BUFFER);
  serial_write_power_data(POWER_BUFFER, POWER_BUFFER_SIZE);
  sd_write_power_data(DATA_FILE, POWER_BUFFER, POWER_BUFFER_SIZE);
  Serial.print(F(","));
  DATA_FILE.print(",");
  MOS_ADCS.read_values(MOS_BUFFER);
  serial_write_adc_group_data(MOS_BUFFER, MOS_BUFFER_SIZE);
  sd_write_adc_group_data(DATA_FILE, MOS_BUFFER, MOS_BUFFER_SIZE);
  Serial.print(F(","));
  DATA_FILE.print(",");
 
  i2c_select_channel(NO_SENSORS);
  i2c_read_channel_power(POWER_SENSOR, POWER_BUFFER);
  serial_write_power_data(POWER_BUFFER, POWER_BUFFER_SIZE);
  sd_write_power_data(DATA_FILE, POWER_BUFFER, POWER_BUFFER_SIZE);
  Serial.print(F(","));
  DATA_FILE.print(",");
  ELECTROCHEM_ADCS.read_values(ELECTROCHEM_BUFFER);
  serial_write_adc_group_data(ELECTROCHEM_BUFFER, ELECTROCHEM_BUFFER_SIZE);
  sd_write_adc_group_data(DATA_FILE, ELECTROCHEM_BUFFER, ELECTROCHEM_BUFFER_SIZE);
  Serial.print(F(","));
  DATA_FILE.print(",");
  
  i2c_select_channel(CO_SENSORS);
  i2c_read_channel_power(POWER_SENSOR, POWER_BUFFER);
  serial_write_power_data(POWER_BUFFER, POWER_BUFFER_SIZE);
  sd_write_power_data(DATA_FILE, POWER_BUFFER, POWER_BUFFER_SIZE);
  Serial.print(F(","));
  DATA_FILE.print(",");
  ELECTROCHEM_ADCS.read_values(ELECTROCHEM_BUFFER);
  serial_write_adc_group_data(ELECTROCHEM_BUFFER, ELECTROCHEM_BUFFER_SIZE);
  sd_write_adc_group_data(DATA_FILE, ELECTROCHEM_BUFFER, ELECTROCHEM_BUFFER_SIZE);
  Serial.print(F(","));
  DATA_FILE.print(",");

  i2c_select_channel(OX_SENSORS);
  i2c_read_channel_power(POWER_SENSOR, POWER_BUFFER);
  serial_write_power_data(POWER_BUFFER, POWER_BUFFER_SIZE);
  sd_write_power_data(DATA_FILE, POWER_BUFFER, POWER_BUFFER_SIZE);
  Serial.print(F(","));
  DATA_FILE.print(",");
  ELECTROCHEM_ADCS.read_values(ELECTROCHEM_BUFFER);
  serial_write_adc_group_data(ELECTROCHEM_BUFFER, ELECTROCHEM_BUFFER_SIZE);
  sd_write_adc_group_data(DATA_FILE, ELECTROCHEM_BUFFER, ELECTROCHEM_BUFFER_SIZE);
  Serial.print(F(","));
  DATA_FILE.print(",");

  i2c_select_channel(NO2_SENSORS);
  i2c_read_channel_power(POWER_SENSOR, POWER_BUFFER);
  serial_write_power_data(POWER_BUFFER, POWER_BUFFER_SIZE);
  sd_write_power_data(DATA_FILE, POWER_BUFFER, POWER_BUFFER_SIZE);
  Serial.print(F(","));
  DATA_FILE.print(",");
  ELECTROCHEM_ADCS.read_values(ELECTROCHEM_BUFFER);
  serial_write_adc_group_data(ELECTROCHEM_BUFFER, ELECTROCHEM_BUFFER_SIZE);
  sd_write_adc_group_data(DATA_FILE, ELECTROCHEM_BUFFER, ELECTROCHEM_BUFFER_SIZE);
  Serial.print(F(","));
  DATA_FILE.print(",");
  
  i2c_select_channel(CO2_SENSORS);
  i2c_read_channel_power(POWER_SENSOR, POWER_BUFFER);
  serial_write_power_data(POWER_BUFFER, POWER_BUFFER_SIZE);
  sd_write_power_data(DATA_FILE, POWER_BUFFER, POWER_BUFFER_SIZE);
  Serial.print(F(","));
  DATA_FILE.print(",");
  CO2_ADCS.read_values(CO2_BUFFER);
  serial_write_adc_group_data(CO2_BUFFER, CO2_BUFFER_SIZE);
  sd_write_adc_group_data(DATA_FILE, CO2_BUFFER, CO2_BUFFER_SIZE);
  Serial.print(F(","));
  DATA_FILE.print(",");

  i2c_select_channel(PUMP_SENSORS);
  i2c_read_channel_power(POWER_SENSOR, POWER_BUFFER);
  serial_write_power_data(POWER_BUFFER, POWER_BUFFER_SIZE);
  sd_write_power_data(DATA_FILE, POWER_BUFFER, POWER_BUFFER_SIZE);
  Serial.print(F(","));
  DATA_FILE.print(",");

  i2c_select_channel(META_SENSORS);
  META_ADCS.read_values_nd(META_BUFFER);
  serial_write_adc_group_data(META_BUFFER, META_BUFFER_SIZE);
  sd_write_adc_group_data(DATA_FILE, META_BUFFER, META_BUFFER_SIZE);

  Serial.print(F("\r\n"));
  DATA_FILE.print("\r\n");
  DATA_FILE.close();

  delay(500);
}
