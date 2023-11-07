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
    void setLiveWeather(bool val);
    bool getLiveWeather();
    void setExit(bool val);
    bool getExit();
    void setHour(int val);
    int getHour();
    void setMinute(int val);
    int getMinute();
  protected:
    WeatherData();
    ~WeatherData();
  private:
    static WeatherData* instance;
    std::mutex dataMutex;
    bool liveWeather = false;
    bool exit = false;
    int hour = 2;
    int minute = 17;
};

#endif
