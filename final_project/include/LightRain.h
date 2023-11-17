/*
 * File: LightRain.h
 * Author: Jared McKneely
 * Description: Header file for the LightRain class
 */

#ifndef _LIGHT_RAIN_H
#define _LIGHT_RAIN_H

#include "BaseWeatherCondition.h"
#include "SkyBox.h"

class LightRain : public BaseWeatherCondition {
  public:
    LightRain();
    ~LightRain();
    void draw();
  protected:
    SkyBox* sky;
};

#endif
