/****************************************************************************//*
 * @file    BOCS_Serial.h
 * @author  Killian Murphy <killian.murphy@york.ac.uk>
 * @date    23 November 2018
 * @brief   Thin wrapper around Arduino Serial library to provide some BOCS-
 *          specific functionality.
 ******************************************************************************/
#ifndef __BOCS_SERIAL_H__
#define __BOCS_SERIAL_H__
/******************************************************************************/
#include <Arduino.h>
/****************************************************************************//*
 * @brief  Configuration macros specifying some serial communication properties.
 *
 * BAUD_RATE is the desired baud rate for USB serial communication.
 ******************************************************************************/
#define BAUD_RATE 115200
/****************************************************************************//*
 * @brief  Initialise the USB Serial interface.
 *
 * @param[in]  rate  The desired baud rate for USB serial interface.
 ******************************************************************************/
void serial_init(uint32_t rate);
/****************************************************************************//*
 * @brief  Write a buffer of power data to the USB serial interface.
 *
 * @param[in]  data      The power data.
 * @param[in]  data_len  The length of the power data buffer.
 ******************************************************************************/
// TODO: CONSIDER REFACTORING THIS TO BE A METHOD OF ADCGroup
void serial_write_power_data(float *data, uint8_t data_len);
#endif
