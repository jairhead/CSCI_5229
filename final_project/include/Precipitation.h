/*
 * File: Precipitation.h
 * Author: Jared McKneely
 * Description: Header file for the Precipitation class
 */

#ifndef _LIGHT_RAIN_H
#define _LIGHT_RAIN_H

#include <cstdlib>
#include "BaseWeatherCondition.h"
#include "Utilities.h"
#include "SkyBox.h"
#include "Landscape.h"
#include "LightManager.h"
#include "AnalogClock.h"

class Precipitation : public BaseWeatherCondition {
  public:
    Precipitation(LightManager* l);
    ~Precipitation();
    void draw();
  private:
    // Private methods
    void landscape();
    void sky();
    void sun();
    void moon();
    void rain();
    void snow();
    void mix();
    void fog();
    void updatePrecip();

    // Private scene variables
    SkyBox* skyBox;
    Landscape* land;
    WeatherData* data = nullptr;
    LightManager* light = nullptr;

    // Sky colors
    float skyColor[4] = {0.55, 0.55, 0.55, 1.0};
    const float day[4] = {0.55, 0.55, 0.55, 1.0};
    const float night[4] = {0.0, 0.0, 0.0, 1.0};
    float rStep = 0.0;
    float gStep = 0.0;
    float bStep = 0.0;
    int lightFactor = 70;

    // Rain & snow variables
    int rainDrop;
    int snowFlake;
    int numPrecip = 20;
    float precipPos[1000][3];
    float rainFallSpeed = 0.15;
    float snowFallSpeed = 0.05;
    float precipXMax = 2.0;
    float precipXMin = -2.0;
    float precipYMax = 3.0;
    float precipYMin = 0.0;
    float precipZMax = 2.0;
    float precipZMin = -2.0;
    char weatherCondition;
};

#endif
