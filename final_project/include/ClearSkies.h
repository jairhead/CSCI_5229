/*
 * File: ClearSkies.h
 * Author: Jared McKneely
 * Description: Header file for the ClearSkies class
 */

#ifndef _CLEAR_SKIES_H
#define _CLEAR_SKIES_H

#include <cstdlib>
#include "BaseWeatherCondition.h"
#include "Utilities.h"
#include "SkyBox.h"
#include "Landscape.h"
#include "LightManager.h"
#include "AnalogClock.h"

class ClearSkies : public BaseWeatherCondition {
  public:
    ClearSkies(LightManager* l);
    ~ClearSkies();
    void draw();
  private:
    // Private methods
    void landscape();
    void sky();
    void sun();
    void moon();
    void fog(float density);

    // Private scene variables
    SkyBox* skyBox;
    Landscape* land;
    WeatherData* data = nullptr;
    LightManager* light = nullptr;

    // Sky colors
    float skyColor[4] = {0.00, 0.15, 0.89, 1.00};
    const float day[4] = {0.00, 0.15, 0.89, 1.00};
    const float night[4] = {0.00, 0.00, 0.00, 1.00};
    float rStep = 0.0;
    float gStep = 0.0;
    float bStep = 0.0;
    int lightFactor = 70;
};

#endif
