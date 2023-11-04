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
  public:
    static WeatherData* getInstance();
    void setExit(bool val);
    bool getExit();
    void setLiveWeather(bool val);
    bool getLiveWeather();
  private:
    WeatherData();
    ~WeatherData();
    static WeatherData* instance;
    std::mutex dataMutex;
    bool liveWeather = false;
    bool end = false;
};

#endif
