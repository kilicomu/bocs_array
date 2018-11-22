/***************************************************************************//**
 * @file    main.cpp
 * @author  Killian Murphy <killian.murphy@york.ac.uk>
 * @date    21 November 2018
 * @brief   Read data from attached sensors and send over USB serial.
 ******************************************************************************/
#include <Arduino.h>
#include <BOCS_I2C.h>
/***************************************************************************//**
 * @brief  Code that will run before the main execution loop.
 ******************************************************************************/
void setup() {
  Serial.begin(9600);
  while (!Serial) {}
  Serial.println("INFO: INITIALISED SERIAL");

  i2c_init();
  Serial.println("INFO: INITIALISED I2C");

  uint8_t i2c_status = i2c_select_channel(NO_SENSORS);
  Serial.print("INFO: I2C STATUS IS ");
  Serial.println(i2c_status);
}
/***************************************************************************//**
 * @brief  The main execution loop.
 ******************************************************************************/
void loop() {
}
