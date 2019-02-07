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
#include <SD.h>
/******************************************************************************/
class ADCGroup {
  private:
    uint8_t number_of_adcs;
    uint8_t adc_buffer_length;
    int16_t *adc_buffer;
    Adafruit_ADS1115 *adcs;
  public:
    ADCGroup (uint8_t);
    void init(uint8_t);
    void init_all(void);
    void read_values(void);
    void read_values_nd(void);
    void set_gain(uint8_t, adsGain_t);
    void set_gain_all(adsGain_t);
    void write_values_to_serial(void);
    void write_values_to_sd(File);
};
#endif
