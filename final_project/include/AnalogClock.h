/*
 * File: AnalogClock.h
 * Author: Jared McKneely
 * Description: Header file for the AnalogClock class
 */

#ifndef _ANALOG_CLOCK_H
#define _ANALOG_CLOCK_H

#include "BaseObject.h"
#include "WeatherData.h"
#include "Utilities.h"

class AnalogClock : public BaseObject {
  public:
    AnalogClock();
    ~AnalogClock();
    void color(double r, double g, double b);
    void setTextureFactor(float tf);
    void setTexture(unsigned int *tex);
    void draw();
  protected:
    // Color & lighting variables (tower)
    float tColorArray[3] = {0.05, 0.05, 0.05};
    float tSpecularArray[4] = {0.7, 0.7, 0.7, 1.0};
    float tEmissionArray[4] = {0.0, 0.0, 0.0, 1.0};
    float tDiffuseArray[4] = {0.1, 0.1, 0.1, 1.0};

    // Color & lighting variables (clock face)
    float cColorArray[3] = {1.0, 1.0, 1.0};
    float cSpecularArray[4] = {1.0, 1.0, 1.0, 1.0};
    float fEmissionArray[4] = {0.86, 0.65, 0.32, 1.0};
    float cEmissionArray[4] = {0.0, 0.0, 0.0, 1.0};
    float cDiffuseArray[4] = {0.9, 0.9, 0.9, 1.0};

    // Geometry variables
    const int d = 5;
    double r = 1.0;
    double phi = 90.0;

    // Texture variables
    float texFact = 1.0;

    // Protected member functions
    double sine(double angle);
    double cosine(double angle);
    void drawClockFace(double y);
    void drawClockRim(double y);
    void drawClockMarkers(double y);
    void drawHourHand(double y);
    void drawMinuteHand(double y);

    // Objects
    WeatherData* data = nullptr;
    float clockPolePos[3] = {1.0, 1.0, 1.0};
    int clockPole;
};

#endif
