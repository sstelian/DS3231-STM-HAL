/**
* This library is an extension to the original Maxim Integrated Products, Inc. ds3231 mbed library ported to
* STM HAL by Stelian Saracut, 2023
*/

#include "DS3231.hxx"

// set_time wrapper that uses standard time.h struct tm instead of the custom made ds3231 struct
uint16_t DS3231::setTime(struct tm* timeStruct)
{
  uint16_t returnValue;

  ds3231_time_t ds3231_time;
  ds3231_calendar_t ds3231_calendar;

  ds3231_time.seconds = timeStruct->tm_sec;
  ds3231_time.minutes = timeStruct->tm_min;
  ds3231_time.hours = timeStruct->tm_hour;
  ds3231_time.am_pm = false;
  ds3231_time.mode = false; // 24 hour mode

  returnValue = set_time(ds3231_time);
  if (returnValue != 0) // set_time failed
  {
    return returnValue;
  }

  ds3231_calendar.day = timeStruct->tm_wday + 1;
  ds3231_calendar.date = timeStruct->tm_mday;
  ds3231_calendar.month = timeStruct->tm_mon + 1;
  ds3231_calendar.year = timeStruct->tm_year % 100;

  returnValue = set_calendar(ds3231_calendar);

  return returnValue;
}

// set_time wrapper that uses standard time.h time_t instead of the custom made ds3231 data types
uint16_t DS3231::setTime(time_t time)
{
  uint16_t returnValue;

  struct tm* timeStruct;

  timeStruct = localtime(&time);

  returnValue = setTime(timeStruct);

  return returnValue;
}

// checks presence of DS3231
// returns true if DS3231 is present or false otherwise
// presence is checked by trying to read the Control/Status register
//
// WARNING: It is highly advised to call this method and only call other methods if this returns true!
bool DS3231::RTCPresent()
{
  ds3231_cntl_stat_t rtc_status;
  uint16_t returnValue;

  returnValue = get_cntl_stat_reg(&rtc_status);

  return (returnValue == 0);
}

// checks if DS3231 is running by checking the OSF flag
// returns true if DS3231 is running or false otherwise
// if this returns false, the date and time inside the DS3231 are not valid and need to be set
//
// WARNING: It is highly advised to call this method and only use the date and time from the DS3231 if this returns true!
bool DS3231::RTCRunning()
{
  ds3231_cntl_stat_t rtc_status;
  uint16_t returnValue;

  returnValue = get_cntl_stat_reg(&rtc_status);

  // if OSF set, RTC is not running, data is not valid
  return (returnValue == 0) && !(rtc_status.status & OSF);
}
