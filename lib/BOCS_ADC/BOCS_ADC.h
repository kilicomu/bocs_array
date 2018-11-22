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
/******************************************************************************/
class ADCGroup {
  private:
    static const uint8_t NUMBER_OF_ADCS = 0x03;
    Adafruit_ADS1115 adcs[NUMBER_OF_ADCS];
  public:
    ADCGroup (void);
    ADCGroup (uint8_t, uint8_t, uint8_t);
    void adc_init(uint8_t);
    void adc_init_all(void);
    int16_t read_value(uint8_t);
    void read_values(int16_t*);
};
#endif
