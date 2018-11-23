/****************************************************************************//*
 * @file    BOCS_RTC.h
 * @author  Killian Murphy <killian.murphy@york.ac.uk>
 * @date    23 November 2018
 * @brief   Thin wrapper around Adafruit RTC library to provide required BOCS
 *          RTC functionality.
 ******************************************************************************/
#ifndef __BOCS_RTC_H__
#define __BOCS_RTC_H__
/******************************************************************************/
#include <Arduino.h>
#include <RTClib.h>
/******************************************************************************/
/****************************************************************************//*
 * @brief  Initialise a DS1307 RTC Module.
 *
 * @param[inout]  rtc  The DS1307 instance to initialise.
 ******************************************************************************/
void rtc_init(RTC_DS1307 rtc);
/****************************************************************************//*
 * @brief  Return the current UNIX timestamp.
 *
 * @param[in]  rtc  DS1307 instance from which we will get a timestamp.
 *
 * @return          UNIX timestamp.
 ******************************************************************************/
uint32_t rtc_get_unix_time(RTC_DS1307 rtc);
#endif
