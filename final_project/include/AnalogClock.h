/*
 * File: AnalogClock.h
 * Author: Jared McKneely
 * Description: Header file for the AnalogClock class
 */

#ifndef _ANALOG_CLOCK_H
#define _ANALOG_CLOCK_H

#include "BaseObject.h"

class AnalogClock : public BaseObject {
  public:
    AnalogClock();
    ~AnalogClock();
    void color(double r, double g, double b);
    void setTextureFactor(float tf);
    void setTexture(unsigned int *tex);
    void draw();
  protected:
    // Color & lighting variables
    float colorArray[3] = {1.0, 1.0, 1.0};
    float specularArray[4] = {0.8, 0.8, 0.8, 1.0};
    float emissionArray[4] = {0.0, 0.0, 0.0, 1.0};
    float diffuseArray[4] = {0.1, 0.1, 0.1, 1.0};

    // Geometry variables
    const int d = 5;

    // Texture variables
    float texFact = 1.0;

    // Protected member functions
    double sine(double angle);
    double cosine(double angle);
    void drawFace(double r, double y, double yNorm);
};

#endif
