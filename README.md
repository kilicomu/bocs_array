# BOCS Sensor Array Control

## Overview
This repository contains a simple program for getting and logging sensor values from the various sensors inside a Box Of Clustered Sensors (BOCS) instrument. Using an [Arduino Uno](https://store.arduino.cc/products/arduino-uno-rev3/) and [logging shield](http://www.velleman.co.uk/contents/en-uk/p908_Velleman_Arduino%E2%84%A2_Data_logging_shield.html), data is recorded to both an SD card and via USB serial, providing some redundancy.

For more information about the BOCS instrument, please see the BOCS project website: **TODO**

## Setup
This program supports build and installation via either the Arduino IDE or PlatformIO. To set up the Arduino IDE, please see ['Getting Started with Arduino products'](https://www.arduino.cc/en/Guide). To set up PlatformIO, please see the [PlatformIO installation guides](https://platformio.org/install/).

This program is built with a few libraries, specifically:

* [Adafruit_ADS1X15](https://github.com/adafruit/Adafruit_ADS1X15) - tested with version 2.3.0
* [Adafruit_INA219](https://github.com/adafruit/Adafruit_INA219) - tested with version 1.1.1
* [RTClib](https://github.com/adafruit/RTClib) - tested with version 1.1.1

When building the project with PlatformIO, the installation of these libraries will happen automatically! With the Arduino IDE, these libraries will need to be installed by you - you can find out how to do this from the [Arduino documentation](https://docs.arduino.cc/learn/starting-guide/software-libraries).

**Please note:** This program assumes that you have already set the time on the DS1307 real time clock that is attached to the data logging shield. If you haven't, please do so before installing this program to the Arduino - you can find an example of how to do this [here](https://learn.adafruit.com/ds1307-real-time-clock-breakout-board-kit/understanding-the-code).

## Installation

### Arduino IDE
1. Clone a copy of this repository or download it as a ZIP from the Releases page and extract it to your filesystem
2. Open the `src/bocs_array.ino` file in the Arduino IDE
3. Ensure that you have installed the required libraries as described in the `Setup` section of this README
4. With your Arduino Uno attached to a USB port on your computer, follow the generic instructions for uploading an Arduino sketch to a device, available [here](https://docs.arduino.cc/software/ide-v1/tutorials/arduino-ide-v1-basics#uploading)

### PlatformIO IDE
1. Clone a copy of this repository or download it as a ZIP from the Releases page and extract it to your filesystem
2. Open the `bocs_array` directory with 'Open Project' from inside PlatformIO IDE
3. Under 'uno'->'General' in the PlatformIO 'Project Tasks' pane, select 'Build' to set up the project and build the program
4. With your Arduino Uno attached to a USB port on your computer, under 'uno'->'General' in the PlatformIO 'Project Tasks' pane, select 'Upload' to upload the `bocs_array` program to the Arduino

### PlatformIO CLI
1. Clone a copy of this repository or download it as a ZIP from the Releases page and extract it to your filesystem
2. In a terminal, change working directory to `bocs_array`
3. Run the `platformio run` command to complete necessary housekeeping tasks and build the `bocs_array` program
4. With the Arduino Uno attached to a USB port on your computer, run the `platformio run --target upload` command to upload the `bocs_array` program to the Arduino

## Contact
Please report any issues / suggestions to Pete Edwards <pete.edwards@york.ac.uk> in the first instance, as well as opening a repository issue.
