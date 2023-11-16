/*
 * File: Scene.h
 * Author: Jared McKneely
 * Description: Contains logice to animate the entire weather scene
 */

#ifndef _WEATHER_SCENE_H
#define _WEATHER_SCENE_H

#include "WeatherData.h"
#include "LightManager.h"
#include "Utilities.h"
#include "Axes.h"

#include "SkyBox.h"
#include "AnalogClock.h"

class Scene {
  public:
    Scene();
    ~Scene();
    void draw();
  private:
    void drawSky();
    void drawLandscape();
    void drawLight();
    bool drawAxes = true;
    WeatherData* data = nullptr;
    LightManager *light = nullptr;
    Axes *xyz;
    SkyBox* sky;
    AnalogClock* clock;
};

#endif
