/****************************************************************************//*
 * @file    main.cpp
 * @author  Killian Murphy <killian.murphy@york.ac.uk>
 * @date    2021-12-16
 * @brief   Main sensor reading loop for BOCS instrument.
 ******************************************************************************/
#include <Arduino.h>
#include <Adafruit_ADS1015.h>
#include <Adafruit_INA219.h>
#include <RTClib.h>
#include <SD.h>
#include <SPI.h>
#include <Wire.h>
/******************************************************************************/
#define BAUD_RATE 9600

#define I2C_MUX_ADDRESS            0x70
#define I2C_ADC_1_ADDRESS          0x48
#define I2C_ADC_2_ADDRESS          0x49
#define I2C_ADC_3_ADDRESS          0x4A
#define I2C_ADC_4_ADDRESS          0x4B
#define I2C_POWER_SENSOR_1_ADDRESS 0x40
#define I2C_POWER_SENSOR_2_ADDRESS 0x41

#define MUX_MOS_SENSOR_CHANNEL  0x00
#define MUX_NO_SENSOR_CHANNEL   0x01
#define MUX_CO_SENSOR_CHANNEL   0x02
#define MUX_OX_SENSOR_CHANNEL   0x03
#define MUX_NO2_SENSOR_CHANNEL  0x04
#define MUX_CO2_SENSOR_CHANNEL  0x05
#define MUX_PUMP_SENSOR_CHANNEL 0x06
#define MUX_META_SENSOR_CHANNEL 0x07

#define ADC_NUM_MOS_ADCS         0x04
#define ADC_NUM_ELECTROCHEM_ADCS 0x03
#define ADC_NUM_CO2_ADCS         0x03
#define ADC_NUM_META_ADCS        0x02
/******************************************************************************/
void    i2c_read_channel_adcs(Adafruit_ADS1115 *adcs, int adc_count);
void    i2c_read_power_sensor(Adafruit_INA219 power_sensor);
uint8_t mux_select_channel(uint8_t channel);
/******************************************************************************/
Adafruit_ADS1115 adcs[4] = {
  Adafruit_ADS1115(I2C_ADC_1_ADDRESS),
  Adafruit_ADS1115(I2C_ADC_2_ADDRESS),
  Adafruit_ADS1115(I2C_ADC_3_ADDRESS),
  Adafruit_ADS1115(I2C_ADC_4_ADDRESS)
};
Adafruit_INA219 power_sensor_1(I2C_POWER_SENSOR_1_ADDRESS);
Adafruit_INA219 power_sensor_2(I2C_POWER_SENSOR_2_ADDRESS);
File sd_data_file;
char sd_filename[12] = {'\0'};
RTC_DS1307 rtc;
bool sd_initialised = false;
/******************************************************************************/
void setup() {
  // INITIALISE USB SERIAL:
  Serial.begin(BAUD_RATE);
  while(!Serial) {}

  // INITIALISE I2C BUS:
  Wire.begin();

  // INITIALISE RTC:
  if (! rtc.begin()) {
    Serial.println(F("ERROR: COULDN'T INITIALISE RTC!"));
    while(1);
  }

  // ATTEMPT TO INITIALISE SD CARD:
  sd_initialised = SD.begin();
  if (! sd_initialised) {
    Serial.println(F("ERROR: COULDN'T INITIALISE SD!"));
  }

  // INITIALISE MOS CHANNEL ADCS AND POWER SENSORS:
  mux_select_channel(MUX_MOS_SENSOR_CHANNEL);
  power_sensor_1.begin();
  power_sensor_2.begin();
  for (uint8_t i = 0; i < ADC_NUM_MOS_ADCS; ++i) {
    adcs[i].begin();
  }

  // INITIALISE ELECTROCHEM ADCS AND POWER SENSORS:
  for (uint8_t i = MUX_NO_SENSOR_CHANNEL; i < MUX_CO2_SENSOR_CHANNEL; ++i) {
    mux_select_channel(i);
    power_sensor_1.begin();
    for (uint8_t j = 0; j < ADC_NUM_ELECTROCHEM_ADCS; ++j) {
      adcs[j].begin();
    }
  }

  // INITIALISE CO2 ADCS AND POWER SENSORS:
  mux_select_channel(MUX_CO2_SENSOR_CHANNEL);
  power_sensor_1.begin();
  for (uint8_t i = 0; i < ADC_NUM_CO2_ADCS; ++i) {
    adcs[i].begin();
  }

  // INITIALISE PUMP POWER SENSORS:
  mux_select_channel(MUX_PUMP_SENSOR_CHANNEL);
  power_sensor_1.begin();

  // INITIALISE META ADCS:
  mux_select_channel(MUX_META_SENSOR_CHANNEL);
}
/******************************************************************************/
void loop() {
  // TIMESTAMP THE START OF THE MAIN LOOP ITERATION FOR 0.5Hz CONTROL:
  DateTime loop_iteration_start = rtc.now();

  // SET UP SD CARD DATA FILE:
  if (sd_initialised) {
    sprintf(
      sd_filename,
      "%04d%02d%02d.CSV",
      loop_iteration_start.year(),
      loop_iteration_start.month(),
      loop_iteration_start.day()
    );

    sd_data_file = SD.open(sd_filename, FILE_WRITE);

    if (! sd_data_file) {
      Serial.println(F("ERROR: UNABLE TO OPEN SD CARD FILE"));
    }
  }

  // PRINT TIMESTAMP AS FIRST DATA FIELD:
  Serial.print(loop_iteration_start.unixtime());
  Serial.print(F(","));

  if (sd_initialised) {
    sd_data_file.print(loop_iteration_start.unixtime());
    sd_data_file.print(F(","));
  }

  // SAMPLE DATA FROM MOS ADCS AND POWER SENSORS:
  mux_select_channel(MUX_MOS_SENSOR_CHANNEL);
  i2c_read_power_sensor(power_sensor_1);
  i2c_read_power_sensor(power_sensor_2);
  i2c_read_channel_adcs(adcs, ADC_NUM_MOS_ADCS);

  // SAMPLE DATA FROM ELECTROCHEM ADCS AND POWER SENSORS:
  for (uint8_t i = MUX_NO_SENSOR_CHANNEL; i < MUX_CO2_SENSOR_CHANNEL; ++i) {
    mux_select_channel(i);
    i2c_read_power_sensor(power_sensor_1);
    i2c_read_channel_adcs(adcs, ADC_NUM_ELECTROCHEM_ADCS);
  }

  // SAMPLE DATA FROM CO2 ADCS AND POWER SENSORS:
  mux_select_channel(MUX_CO2_SENSOR_CHANNEL);
  i2c_read_power_sensor(power_sensor_1);
  i2c_read_channel_adcs(adcs, ADC_NUM_CO2_ADCS);

  // SAMPLE DATA FROM PUMP POWER SENSORS:
  mux_select_channel(MUX_PUMP_SENSOR_CHANNEL);
  i2c_read_power_sensor(power_sensor_1);

  // SAMPLE DATA FROM META ADCS:
  mux_select_channel(MUX_META_SENSOR_CHANNEL);

  uint16_t value_1 = adcs[0].readADC_SingleEnded(0);
  uint16_t value_2 = adcs[0].readADC_SingleEnded(1);

  Serial.print(value_1);
  Serial.print(F(","));

  Serial.print(value_2);
  Serial.print(F(","));

  if (sd_initialised) {
    sd_data_file.print(value_1);
    sd_data_file.print(F(","));

    sd_data_file.print(value_2);
    sd_data_file.print(F(","));
  }

  value_1 = adcs[1].readADC_SingleEnded(0);
  value_2 = adcs[1].readADC_SingleEnded(1);

  Serial.print(value_1);
  Serial.print(F(","));
  Serial.print(value_2);

  if (sd_initialised) {
    sd_data_file.print(value_1);
    sd_data_file.print(F(","));
    sd_data_file.print(value_2);
  }
  
  // WRITE LINE SEPARATOR TO SERIAL / SD CARD AND FLUSH SD CARD WRITE BUFFER:
  Serial.print(F("\r\n"));
  
  if (sd_initialised) {
    sd_data_file.print(F("\r\n"));
    sd_data_file.close();
  }

  // WAIT FOR 2 SECONDS TO HAVE PASSED BEFORE LOOPING:
  while ((rtc.now() - loop_iteration_start).totalseconds() < 2) {}
}
/******************************************************************************/
void i2c_read_channel_adcs(Adafruit_ADS1115 *adcs, int adc_count) {
  for (uint8_t i = 0; i < adc_count; ++i) {
    int16_t value_1 = adcs[i].readADC_Differential_0_1();
    int16_t value_2 = adcs[i].readADC_Differential_2_3();

    Serial.print(value_1);
    Serial.print(F(","));

    Serial.print(value_2);
    Serial.print(F(","));

    if (sd_initialised) {
      sd_data_file.print(value_1);
      sd_data_file.print(F(","));

      sd_data_file.print(value_2);
      sd_data_file.print(F(","));
    }
  }
  

}

void i2c_read_power_sensor(Adafruit_INA219 power_sensor) {
  float values[3] = {
    ((float) power_sensor.getBusVoltage_V() * 1000) + power_sensor.getShuntVoltage_mV(),
    power_sensor.getCurrent_mA(),
    power_sensor.getPower_mW()
  };

  for (uint8_t i = 0; i < 3; ++i) {
    Serial.print(values[i]);
    Serial.print(F(","));

    if (sd_initialised) {
      sd_data_file.print(values[i]);
      sd_data_file.print(F(","));
    }
  }
}

uint8_t mux_select_channel(uint8_t channel) {
  Wire.beginTransmission(I2C_MUX_ADDRESS);
  Wire.write(1 << channel);
  return Wire.endTransmission();
}
