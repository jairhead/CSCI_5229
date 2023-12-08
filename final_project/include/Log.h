/*
 * File: Log.h
 * Author: Jared McKneely
 * Description: Implementation file for the Log class, a child
 *              class of the BaseObject abstract class.
 */

#ifndef _LOG_H
#define _LOG_H

#include "BaseObject.h"
#include "Utilities.h"

class Log : public BaseObject {
  public:
    Log();
    ~Log();
    void setTextureFactor(float tf);
    void setTheta(double th);
    void setPhi(double ph);
    void setLogCircularTexture(unsigned int *tex);
    void setLogTopTexture(unsigned int *tex);
    void draw();
  protected:
    // Protected member functions
    void drawCircumference(double r, double l);
    void drawTop(double r, double l);
    void drawBottom(double r);

    // Geometry variables
    const int d = 30;
    double phi = 0.0;

    // Texture variables
    float texFact = 1.0;
    unsigned int *logCircularTexture;
    unsigned int *logTopTexture;

    // Color & lighting variables
    float colorArray[4] = {1.0, 1.0, 1.0, 1.0};
    float specularArray[4] = {0.25, 0.25, 0.25, 1.0};
    float emissionArray[4] = {0.0, 0.0, 0.0, 1.0};
    float diffuseArray[4] = {0.1, 0.1, 0.1, 1.0};
};

#endif