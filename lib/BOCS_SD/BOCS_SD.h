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
 * @brief  Initialise Velleman data logging shield SD card capabilities.
 ******************************************************************************/
void sd_init(void);
/****************************************************************************//*
 * @brief Write a buffer of power sensor data to a file on the SD card.
 *
 * @param[in]  file      The file on the SD card to write to.
 * @param[in]  data      The data from the power sensor to be written to SD.
 * @param[in]  data_len  The length of the power data buffer.
 ******************************************************************************/
void sd_write_power_data(File file, float *data, uint8_t data_len);
#endif
