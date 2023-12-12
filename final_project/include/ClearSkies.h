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
    void sunrise();
    void sun();
    void sunset();
    void moon();
    void fog(float density);
    void stars(int timeOfDay);

    // Private scene variables
    SkyBox* skyBox;
    Landscape* land;
    WeatherData* data = nullptr;
    LightManager* light = nullptr;

    // Texture variables
    unsigned int textures[1];

    // Sky colors
    float skyColor[4] = {0.00, 0.15, 0.89, 1.00};
    const float day[4] = {0.00, 0.15, 0.89, 1.00};
    const float night[4] = {0.00, 0.00, 0.00, 1.00};
    float rStep = 0.0;
    float gStep = 0.0;
    float bStep = 0.0;
    int lightFactor = 70;

    // Sunrise and sunset params
    int currHr = 12;
    int currMin = 0;
    int sunriseHr = 6;
    int sunriseMin = 30;
    int sunsetHr = 18;
    int sunsetMin = 30;
    int daytimeDiff = 0;
    int sunriseDiff = 0;
    int sunsetDiff = 0;
    double orbitDist = 3.0;
    double zDist = -1.5;

    // Star variables
    float starColor[4] = {0.00, 0.15, 0.89, 1.00};
    const float star[4] = {0.93, 0.93, 0.93, 1.00};
    float starRStep = 0.0;
    float starGStep = 0.0;
    float starBStep = 0.0;
    int starObj;
    int numStars = 100;
    int twinkleVal = 3;
    float starPos[100][3];
    bool twinkles[100];
    float starXMax = 5.0;
    float starXMin = -5.0;
    float starZMax = 5.0;
    float starZMin = -5.0;
};

#endif
