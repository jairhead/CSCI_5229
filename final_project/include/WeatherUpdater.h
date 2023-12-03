/*
 * File: WeatherUpdater.h
 * Author: Jared McKneely
 * Description: A class that will make NOAA API calls and provide an updater service
 *              for WeatherData
 */

#ifndef _WEATHER_UPDATER_H
#define _WEATHER_UPDATER_H

#include <iostream>
#include <unistd.h>
#include "WeatherData.h"

class WeatherUpdater {
  public:
    WeatherUpdater();
    ~WeatherUpdater();
    void updateThread(int loopTime);
    void demoThread();
  private:
    void demoIncrementWeatherCondition(char &wc);
    bool sendRequest();
    WeatherData* data = nullptr;
};

#endif
