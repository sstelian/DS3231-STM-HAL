/**
* This library is an extension to the original Maxim Integrated Products, Inc. ds3231 mbed library ported to
* STM HAL by Stelian Saracut, 2023
*/

#pragma once

#include "ds3231.hxx"

class DS3231: public Ds3231
{
public:
  DS3231(I2C_HandleTypeDef *_I2C_Handle):
    Ds3231(_I2C_Handle){};
  
  // set_time wrapper that uses standard time.h struct tm instead of the custom made ds3231 struct
  uint16_t setTime(struct tm* timeStruct);

  // set_time wrapper that uses standard time.h time_t instead of the custom made ds3231 data types
  uint16_t setTime(time_t time);

  // checks presence of DS3231
  // returns true if DS3231 is present or false otherwise
  // presence is checked by trying to read the Control/Status register
  //
  // WARNING: It is highly advised to call this method and only call other methods if this returns true!
  bool RTCPresent();

  // checks if DS3231 is running by checking the OSF flag
  // returns true if DS3231 is running or false otherwise
  // if this returns false, the date and time inside the DS3231 are not valid and need to be set
  //
  // WARNING: It is highly advised to call this method and only use the date and time from the DS3231 if this returns true!
  bool RTCRunning();
};
