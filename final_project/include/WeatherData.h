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
    // Instance handlers
    static WeatherData* getInstance();
    static void removeInstance();

    // Variable getters and setters
    void setLiveWeather(bool val);
    bool getLiveWeather();
    void setExit(bool val);
    bool getExit();
    void setHour(int val);
    int getHour();
    void setMinute(int val);
    int getMinute();
  private:
    // Constructor & destructor
    WeatherData();
    ~WeatherData();

    // Instance variables
    static WeatherData* instance;
    std::mutex dataMutex;

    // Data variables
    bool liveWeather = false;
    bool exit = false;
    int hour = 12;
    int minute = 0;
};

#endif
