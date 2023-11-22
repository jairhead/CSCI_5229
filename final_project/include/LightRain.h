/*
 * File: LightRain.h
 * Author: Jared McKneely
 * Description: Header file for the LightRain class
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

class LightRain : public BaseWeatherCondition {
  public:
    LightRain(LightManager* l);
    ~LightRain();
    void draw();
  private:
    // Private methods
    void landscape();
    void sky();
    void sun();
    void moon();
    void rain();
    void fog();

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
    
};

#endif
