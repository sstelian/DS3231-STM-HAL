# DS3231-STM-HAL
Original Maxim Integrated Products, Inc. ds3231 mbed library ported to
STM HAL by Stelian Saracut, 2023

Use ds3231.hxx for the original functionality of the mbed library.
Use DS3231.hxx for extended functionalities:
    - setTime methods using time.h data types instead of custom made ds3231 types
    - RTCPresent and RTCRunning methods to check the state of the RTC

Tested with STM32L476RGTx.

The software is provided "as is". Read the full ds3231.hxx license.