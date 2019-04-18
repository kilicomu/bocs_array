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
  
  if (count > 2) {
    adc_buffer = (int16_t *) malloc(sizeof(int16_t) * adc_buffer_length);
  }

  if (count < 3) {
    adc_u_buffer = (uint16_t *) malloc(sizeof(uint16_t) * adc_buffer_length);
  }

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
void ADCGroup::read_values(void) {
  for (uint8_t i = 0; i < number_of_adcs; ++i) {
    adc_buffer[(2 * i)] = adcs[i].readADC_Differential_0_1();
    adc_buffer[((2 * i) + 1)] = adcs[i].readADC_Differential_2_3();
  }
}
/******************************************************************************/
void ADCGroup::read_values_nd(void) {
  for (uint8_t i = 0; i < number_of_adcs; ++i) {
    adc_u_buffer[(2 * i)] = adcs[i].readADC_SingleEnded(0);
    adc_u_buffer[((2 * i) + 1)] = adcs[i].readADC_SingleEnded(1);
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
/******************************************************************************/
void ADCGroup::write_values_to_serial(void) {
  uint8_t i = 0;
  for (i = 0; i < (adc_buffer_length - 1); ++i) {
    Serial.print(adc_buffer[i]);
    Serial.print(F(","));
  }
  Serial.print(adc_buffer[i]);
}
/******************************************************************************/
void ADCGroup::write_values_to_sd(File file) {
  uint8_t i = 0;
  for (i = 0; i < (adc_buffer_length - 1); ++i) {
    file.print(adc_buffer[i]);
    file.print(F(","));
  }
  file.print(adc_buffer[i]);
}
/******************************************************************************/
void ADCGroup::write_u_values_to_serial(void) {
  uint8_t i = 0;
  for (i = 0; i < (adc_buffer_length - 1); ++i) {
    Serial.print(adc_u_buffer[i]);
    Serial.print(F(","));
  }
  Serial.print(adc_u_buffer[i]);
}
/******************************************************************************/
void ADCGroup::write_u_values_to_sd(File file) {
  uint8_t i = 0;
  for (i = 0; i < (adc_buffer_length - 1); ++i) {
    file.print(adc_u_buffer[i]);
    file.print(F(","));
  }
  file.print(adc_u_buffer[i]);
}
