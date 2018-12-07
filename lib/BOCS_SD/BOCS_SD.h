/****************************************************************************//*
 * @file    BOCS_SD.h
 * @author  Killian Murphy <killian.murphy@york.ac.uk>
 * @date    23 November 2018
 * @brief   Thin wrappers around Arduino SD library functions.
 ******************************************************************************/
#ifndef __BOCS_SD_H_
#define __BOCS_SD_H_
/******************************************************************************/
#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
/****************************************************************************//*
 * @brief  Configuration macros specifying some SD properties.
 *
 * DATA_FILE_NAME is the name of the data file that will be logged to.
 ******************************************************************************/
#define DATA_FILE_NAME "INDOOR.TXT"
/****************************************************************************//*
 * @brief  Initialise Velleman data logging shield SD card capabilities.
 ******************************************************************************/
void sd_init(void);
/****************************************************************************//*
 * @brief  Write a buffer of ADC group data to a file on the SD card.
 * 
 * @param[in]  file            The file on the SD card to write to.
 * @param[in]  data            The data from the ADC group to be written to SD.
 * @param[in]  data_len        The length of the ADC data buffer.
 ******************************************************************************/
void sd_write_adc_group_data(File file, int16_t *data, uint8_t data_len);
/******************************************************************************/
#endif
