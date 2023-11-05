/*
 * File: WeatherScene.h
 * Author: Jared McKneely
 * Description: Contains logice to animate the entire weather scene
 */

#ifndef _WEATHER_SCENE_H
#define _WEATHER_SCENE_H

#include "WeatherData.h"

class WeatherScene {
  public:
    WeatherScene();
    ~WeatherScene();
    void draw();
  private:
    void setSunPosition();
    void setMoonPosition();
    WeatherData* data = nullptr;
};

#endif
