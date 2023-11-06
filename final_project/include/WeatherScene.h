/*
 * File: WeatherScene.h
 * Author: Jared McKneely
 * Description: Contains logice to animate the entire weather scene
 */

#ifndef _WEATHER_SCENE_H
#define _WEATHER_SCENE_H

#include "WeatherData.h"
#include "LightManager.h"
#include "RectangularPrism.h"
#include "Utilities.h"

class WeatherScene {
  public:
    WeatherScene();
    ~WeatherScene();
    void draw();
  private:
    void drawSky();
    void setSunPosition();
    void setMoonPosition();
    WeatherData* data = nullptr;
    LightManager *light = nullptr;
    RectangularPrism* skyLeft;
    RectangularPrism* skyRight;
    RectangularPrism* skyFront;
    RectangularPrism* skyBack;
    RectangularPrism* skyTop;
};

#endif
