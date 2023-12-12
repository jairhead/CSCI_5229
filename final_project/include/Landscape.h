/*
 * File: Landscape.h
 * Author: Jared McKneely
 * Description: Header file for the Landscape class
 */

#ifndef _LANDSCAPE_H
#define _LANDSCAPE_H

#include "BaseObject.h"
#include "Utilities.h"
#include "WeatherData.h"

#include "AnalogClock.h"
#include "ConiferousTree.h"
#include "Cabin.h"

class Landscape : public BaseObject {
  public:
    Landscape();
    ~Landscape();
    void color(float r, float g, float b);
    void setTextureFactor(float tf);
    void draw();
  protected:
    // Protected methods
    void initializeTrees();

    // Color & lighting variables
    float colorArray[4] = {1.0, 1.0, 1.0, 1.0};
    float specularArray[4] = {0.25, 0.25, 0.25, 1.0};
    float emissionArray[4] = {0.0, 0.0, 0.0, 1.0};

    // Texture variables
    float texFact = 1.0;
    unsigned int textures[11];

    // Object ints
    int grassValley;
    int mountainRim;
    int mountainSnow;

    // Objects
    WeatherData* data = nullptr;
    AnalogClock* clock;
    ConiferousTree* tree1;
    ConiferousTree* tree2;
    ConiferousTree* tree3;
    ConiferousTree* tree4;
    ConiferousTree* tree5;
    Cabin* cabin;
};

#endif
