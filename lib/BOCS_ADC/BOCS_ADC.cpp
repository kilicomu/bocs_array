/****************************************************************************//*
 * @file    BOCS_ADC.cpp
 * @author  Killian Murphy <killian.murphy@york.ac.uk>
 * @date    22 November 2018
 * @brief   BOCS-specific structures/functions involving ADS1115 ADCs.
 ******************************************************************************/
#include "BOCS_ADC.h"
/******************************************************************************/
ADCGroup::ADCGroup(void) {
  adcs[0] = Adafruit_ADS1115(SENSOR_1_ADDR);
  adcs[1] = Adafruit_ADS1115(SENSOR_2_ADDR);
  adcs[2] = Adafruit_ADS1115(SENSOR_3_ADDR);
}
/******************************************************************************/
ADCGroup::ADCGroup(uint8_t addr_1, uint8_t addr_2, uint8_t addr_3) {
  adcs[0] = Adafruit_ADS1115(addr_1);
  adcs[1] = Adafruit_ADS1115(addr_2);
  adcs[2] = Adafruit_ADS1115(addr_3);
}
/******************************************************************************/
void ADCGroup::adc_init(uint8_t adc_number) {
  adcs[adc_number].begin();
}
/******************************************************************************/
void ADCGroup::adc_init_all(void) {
  for (uint8_t i = 0; i < NUMBER_OF_ADCS; ++i) {
    adcs[i].begin();
  }
}
/******************************************************************************/
int16_t ADCGroup::read_value(uint8_t adc_number) {
  return adcs[adc_number].readADC_Differential_0_1();
}

/******************************************************************************/
void ADCGroup::read_values(int16_t *value_buffer) {
  for (uint8_t i = 0; i < NUMBER_OF_ADCS; ++i) {
    value_buffer[i] = adcs[i].readADC_Differential_0_1();
  }
}
/******************************************************************************/
void ADCGroup::print_value(uint8_t adc_number) {
  Serial.print(read_value(adc_number));
}
/******************************************************************************/
void ADCGroup::print_values(void) {
  Serial.print(read_value(0));
  Serial.print(",");
  Serial.print(read_value(1));
  Serial.print(",");
  Serial.print(read_value(2));
}
/******************************************************************************/
void ADCGroup::set_gain(uint8_t adc_number, adsGain_t gain) {
  adcs[adc_number].setGain(gain);
}
/******************************************************************************/
void ADCGroup::set_gain_all(adsGain_t gain) {
  for (uint8_t i = 0; i < NUMBER_OF_ADCS; ++i) {
    adcs[i].setGain(gain);
  }
}

