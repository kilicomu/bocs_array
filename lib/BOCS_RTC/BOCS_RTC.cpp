/****************************************************************************//*
 * @file    BOCS_RTC.cpp
 * @author  Killian Murphy <killian.murphy@york.ac.uk>
 * @date    23 November 2018
 * @brief   Thin wrapper around Adafruit RTC library to provide required BOCS
 *          RTC functionality.
 ******************************************************************************/
#include "BOCS_RTC.h"
/******************************************************************************/
void rtc_init(RTC_DS1307 rtc) {
  if (! rtc.begin()) {
    Serial.println(F("ERROR: COULDN'T FIND RTC!"));
    while(1);
  }
}
/******************************************************************************/
uint32_t rtc_get_unix_time(RTC_DS1307 rtc) {
  DateTime now = rtc.now();
  return now.unixtime();
}
/******************************************************************************/
