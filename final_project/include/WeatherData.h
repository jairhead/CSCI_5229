/*
 * File: WeatherData.h
 * Author: Jared McKneely
 * Description: Singleton, thread-safe data structure
 */

#ifndef _WEATHER_DATA_H
#define _WEATHER_DATA_H

#include <iostream>

class WeatherData {
  private:
    WeatherData();
    ~WeatherData();
    static WeatherData* instance;
  public:
    static WeatherData* getInstance();
};

#endif
