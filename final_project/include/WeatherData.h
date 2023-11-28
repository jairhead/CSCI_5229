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
    void setSunriseHour(int val);
    int getSunriseHour();
    void setSunriseMinute(int val);
    int getSunriseMinute();
    void setSunsetHour(int val);
    int getSunsetHour();
    void setSunsetMinute(int val);
    int getSunsetMinute();
    void setSeason(int seasonNum);
    int getSeason();
    void setCurrentWeatherCondition(char val);
    char getCurrentWeatherCondition();
    void setFog(int val);
    int getFog();
    void setPrecipDensity(int val);
    int getPrecipDensity();
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
    int minute = 00;
    int sunriseHour = 6;
    int sunriseMinute = 30;
    int sunsetHour = 18;
    int sunsetMinute = 30;
    int season = 3;
    char currentWeatherCondition = 'n';
    int fogDensity = 0;
    int precipDensity = 0;
};

#endif
