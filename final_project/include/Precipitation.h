/*
 * File: Precipitation.h
 * Author: Jared McKneely
 * Description: Header file for the Precipitation class
 */

#ifndef _PRECIPITATION_H
#define _PRECIPITATION_H

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
    void fog(float density);
    void updatePrecip();

    // Private scene variables
    SkyBox* skyBox;
    Landscape* land;
    WeatherData* data = nullptr;
    LightManager* light = nullptr;

    // Common sky attributes
    float skyColor[4] = {0.00, 0.15, 0.89, 1.00};
    int lightFactor = 80;

    // Sky colors (rain)
    const float rDay[4] = {0.55, 0.55, 0.55, 1.00};
    const float rNight[4] = {0.00, 0.00, 0.00, 1.00};
    float rRStep = 0.0;
    float rGStep = 0.0;
    float rBStep = 0.0;

    // Sky colors (t-storm)
    const float tDay[4] = {0.27, 0.27, 0.27, 1.00};
    const float tNight[4] = {0.00, 0.00, 0.00, 1.00};
    float tRStep = 0.0;
    float tGStep = 0.0;
    float tBStep = 0.0;
    int lMod = 30;
    int lVal = 10;

    // Sky colors (snow)
    const float sDay[4] = {0.88, 0.88, 0.88, 1.00};
    const float sNight[4] = {0.00, 0.00, 0.00, 1.00};
    float sRStep = 0.0;
    float sGStep = 0.0;
    float sBStep = 0.0;

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
    int snowShader;

    // Color & lighting variables
    float shinyFactor = 1.0;
    float colorArray[4] = {1.0, 1.0, 1.0, 1.0};
    float specularArray[4] = {0.25, 0.25, 0.25, 1.0};
    float emissionArray[4] = {0.0, 0.0, 0.0, 1.0};
};

#endif
