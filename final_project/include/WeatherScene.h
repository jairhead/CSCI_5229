/*
 * File: WeatherScene.h
 * Author: Jared McKneely
 * Description: Contains logice to animate the entire weather scene
 */

#ifndef _WEATHER_SCENE_H
#define _WEATHER_SCENE_H

#include "WeatherData.h"
#include "LightManager.h"
#include "Utilities.h"
#include "Axes.h"

#include "RectangularPrism.h"
#include "AnalogClock.h"

class WeatherScene {
  public:
    WeatherScene();
    ~WeatherScene();
    void draw();
  private:
    void drawSky();
    void drawLandscape();
    bool drawAxes = true;
    WeatherData* data = nullptr;
    LightManager *light = nullptr;
    Axes *xyz;
    RectangularPrism *grass;
    RectangularPrism* skyLeft;
    RectangularPrism* skyRight;
    RectangularPrism* skyFront;
    RectangularPrism* skyBack;
    RectangularPrism* skyTop;
    AnalogClock* clock;
};

#endif
