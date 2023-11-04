/*
 * File: WeatherData.h
 * Author: Jared McKneely
 * Description: Singleton, thread-safe data structure
 */

#ifndef _WEATHER_DATA_H
#define _WEATHER_DATA_H

#include <mutex>
#include <iostream>

class WeatherData {
  private:
    WeatherData();
    ~WeatherData();
    static WeatherData* instance;
    std::mutex dataMutex;
    bool liveWeather = false;
  public:
    static WeatherData* getInstance();
    void setLiveWeather(bool val);
};

#endif
