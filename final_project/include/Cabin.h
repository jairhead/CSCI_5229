/*
 * File: Cabin.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the Cabin class, a child
 *              class of the BaseObject abstract class.
 */

#ifndef _CABIN_H
#define _CABIN_H

#include "BaseObject.h"
#include "WeatherData.h"
#include "Utilities.h"
#include "RectangularPrism.h"
#include "Log.h"

class Cabin : public BaseObject {
  public:
    Cabin();
    ~Cabin();
    void setTextureFactor(float tf);
    void setLogCircularTexture(unsigned int *tex);
    void setLogTopTexture(unsigned int *tex);
    void draw();
  protected:
    // Protected member functions
    void drawPatio();
    void drawLog(double x1, double x2,
                 double y1, double y2,
                 double z1, double z2,
                 double ph);

    // Geometry variables
    const int d = 30;

    // Texture variables
    float texFact = 1.0;
    unsigned int *logCircularTexture;
    unsigned int *logTopTexture;

    // Color & lighting variables
    float colorArray[4] = {1.0, 1.0, 1.0, 1.0};
    float specularArray[4] = {0.25, 0.25, 0.25, 1.0};
    float emissionArray[4] = {0.0, 0.0, 0.0, 1.0};
    float diffuseArray[4] = {0.1, 0.1, 0.1, 1.0};

    // Objects
    WeatherData* data = nullptr;
    Log* log;
};

#endif
