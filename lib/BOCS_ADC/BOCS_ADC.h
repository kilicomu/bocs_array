/****************************************************************************//*
 * @file    BOCS_ADC.h
 * @author  Killian Murphy <killian.murphy@york.ac.uk>
 * @date    22 November 2018
 * @brief   BOCS-specific structures/functions involving ADS1115 ADCs.
 ******************************************************************************/
#ifndef __BOCS_ADC_H__
#define __BOCS_ADC_H__
/******************************************************************************/
#include <Arduino.h>
#include <Adafruit_ADS1015.h>
#include <BOCS_I2C.h>
/****************************************************************************//*
 * @brief  Configuration macros specifying details about BOCS ADCs.
 *
 * ADCS_PER_GROUP is the number of ADS1115 ADCs per group of sensors.
 *
 * ADC_VALUE_BUFFER_LENGTH is the number of uint16_t needed to capture all ADC
 * values in a group (two differential per ADC).
 ******************************************************************************/
#define ADCS_PER_GROUP 0x03
#define ADC_VALUE_BUFFER_LENGTH (2 * ADCS_PER_GROUP)
/******************************************************************************/
class ADCGroup {
  private:
    uint8_t number_of_adcs;
    uint8_t adc_buffer_length;
    Adafruit_ADS1115 *adcs;
  public:
    ADCGroup (uint8_t);
    void init(uint8_t);
    void init_all(void);
    void read_value(uint8_t, int16_t*);
    void read_values(int16_t*);
    void read_value_nd(uint8_t, int16_t*);
    void read_values_nd(int16_t*);
    void set_gain(uint8_t, adsGain_t);
    void set_gain_all(adsGain_t);
};
#endif
