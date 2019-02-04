/****************************************************************************//*
 * @file    BOCS_ADC.cpp
 * @author  Killian Murphy <killian.murphy@york.ac.uk>
 * @date    22 November 2018
 * @brief   BOCS-specific structures/functions involving ADS1115 ADCs.
 ******************************************************************************/
#include "BOCS_ADC.h"
/******************************************************************************/
ADCGroup::ADCGroup(uint8_t count) {
  number_of_adcs = count;
  adc_buffer_length = 2 * count;
  adcs = (Adafruit_ADS1115 *) malloc(sizeof(Adafruit_ADS1115) * number_of_adcs);
  
  for (uint8_t i = 0; i < count; ++i) {
    adcs[i] = Adafruit_ADS1115((i + 0x48));
  }
}
/******************************************************************************/
void ADCGroup::init(uint8_t adc_number) {
  if (adc_number >= 0 && adc_number < number_of_adcs) {
    adcs[adc_number].begin();
  }
}
/******************************************************************************/
void ADCGroup::init_all(void) {
  for (uint8_t i = 0; i < number_of_adcs; ++i) {
    init(i);
  }
}
/******************************************************************************/
void ADCGroup::read_value(uint8_t adc_number, int16_t *value_buffer) {
  if (adc_number >=0 && adc_number < number_of_adcs) {
    value_buffer[0] = adcs[adc_number].readADC_Differential_0_1();
    value_buffer[1] = adcs[adc_number].readADC_Differential_2_3();
  }
}

/******************************************************************************/
void ADCGroup::read_values(int16_t *value_buffer) {
  for (uint8_t i = 0; i < number_of_adcs; ++i) {
    value_buffer[(2 * i)] = adcs[i].readADC_Differential_0_1();
    value_buffer[((2 * i) + 1)] = adcs[i].readADC_Differential_2_3();
  }
}
/******************************************************************************/
void ADCGroup::read_value_nd(uint8_t adc_number, int16_t *value_buffer) {
  if (adc_number >= 0 && adc_number < number_of_adcs) {
    value_buffer[0] = adcs[adc_number].readADC_SingleEnded(0);
    value_buffer[1] = adcs[adc_number].readADC_SingleEnded(1);
  }
}
/******************************************************************************/
void ADCGroup::read_values_nd(int16_t *value_buffer) {
  for (uint8_t i = 0; i < number_of_adcs; ++i) {
    value_buffer[(2 * i)] = adcs[i].readADC_SingleEnded(0);
    value_buffer[((2 * i) + 1)] = adcs[i].readADC_SingleEnded(1);
  }
}
/******************************************************************************/
void ADCGroup::set_gain(uint8_t adc_number, adsGain_t gain) {
  if (adc_number >= 0 && adc_number < number_of_adcs) {
    adcs[adc_number].setGain(gain);
  }
}
/******************************************************************************/
void ADCGroup::set_gain_all(adsGain_t gain) {
  for (uint8_t i = 0; i < number_of_adcs; ++i) {
    set_gain(i, gain);
  }
}
