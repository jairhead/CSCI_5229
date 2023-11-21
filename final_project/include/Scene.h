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

#include "AnalogClock.h"

#include "LightRain.h"

class Scene {
  public:
    Scene();
    ~Scene();
    void draw();
  private:
    // Private member functions
    void drawWeather();
    void drawLandscape();
    void drawLight();
    void drawLightOrbit();

    // Basic objects
    bool drawAxes = true;
    WeatherData* data = nullptr;
    LightManager *light = nullptr;
    Axes *xyz;

    // Scene objects
    AnalogClock* clock;

    // Weather Conditions
    LightRain* lightRain;

    float lightAngle = 0.0;          // Current angle at which the light is located (degrees)
    float lightOrbitRadius = 1.5;    // Radius with which the light will orbit
    float lightHeight = 0.8;         // Y component of light position
    float lightOrbitInc = 2.0;       // Orbit increment
};

#endif
