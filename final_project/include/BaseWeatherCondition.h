/*
 * File: BaseWeatherCondition.h
 * Author: Jared McKneely
 * Description: Header file for the BaseWeatherCondition class, an abstract
 *              class used for defining weather conditions to display.
 */

#ifndef _BASE_WEATHER_CONDITION_H
#define _BASE_WEATHER_CONDITION_H

#include "TopIncludes.h"

class BaseWeatherCondition {
  public:
    void scale(double dx, double dy, double dz) {scaleArray[0] = dx; scaleArray[1] = dy; scaleArray[2] = dz;}
    void translate(double x, double y, double z) {posArray[0] = x; posArray[1] = y; posArray[2] = z;}
    void rotate(double th) {theta = th;}
    double getX() {return posArray[0];}
    double getY() {return posArray[1];}
    double getZ() {return posArray[2];}
    double getTheta() {return theta;}
    void enableLighting() {lightingEnabled = true;}
    void disableLighting() {lightingEnabled = false;}
    virtual void draw() = 0;
    virtual ~BaseWeatherCondition() {}
  protected:
    // Position attributes
    double posArray[3] = {0.0, 0.0, 0.0};
    double scaleArray[3] = {1.0, 1.0, 1.0};
    double theta = 0.0;

    // Lighting attributes
    bool lightingEnabled = true;
};

#endif
