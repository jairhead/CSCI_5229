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
    void setFrontDoorTexture(unsigned int *tex);
    void setRoofTexture(unsigned int *tex);
    void draw();
  protected:
    // Protected methods
    void drawRoof();
    void drawDoor();
    void drawWindow();
    void drawPorch();

    // Texture variables
    float texFact = 1.0;
    unsigned int *fLogCircularTexture;
    unsigned int *fLogTopTexture;
    unsigned int *frontDoorTexture;
    unsigned int *roofTexture;

    // Color & lighting variables
    float colorArray[4] = {1.0, 1.0, 1.0, 1.0};
    float specularArray[4] = {0.25, 0.25, 0.25, 1.0};
    float emissionArray[4] = {0.0, 0.0, 0.0, 1.0};
    float diffuseArray[4] = {0.1, 0.1, 0.1, 1.0};
    float wEmissionArray[4] = {0.86, 0.65, 0.32, 1.0};

    // Weather
    WeatherData* data = nullptr;

    // Front fascia fLogs
    double hUnit = 0.20;
    double lUnit = 0.25;
    Log* fLog1; // Bottom log, left of door
    Log* fLog2; // First stacked log, left of door
    Log* fLog3; // Second stacked log, left of door
    Log* fLog4; // Third stacked log
    Log* fLog5; // Bottom log, right of door / below window
    Log* fLog6; // First stacked log, between door and window
    Log* fLog7; // Second stacked log, between door and window
    Log* fLog8; // First stacked log, right of window
    Log* fLog9; // Second stacked log, right of window

    // Left side fLogs
    Log* lLog1; // Bottom left side log
    Log* lLog2; // First stacked left side log
    Log* lLog3; // Second stacked left side log
    Log* lLog4; // Third stacked left side log

    // Right side fLogs
    Log* rLog1; // Bottom right side log
    Log* rLog2; // First stacked right side log
    Log* rLog3; // Second stacked right side log
    Log* rLog4; // Third stacked right side log

    // Back side fLogs
    Log* bLog1; // Bottom right side fLog
    Log* bLog2; // First stacked right side log
    Log* bLog3; // Second stacked right side log
    Log* bLog4; // Third stacked right side log

    // Front porch
    RectangularPrism* board1; // First board in the porch
    RectangularPrism* board2; // Second board in the porch
    RectangularPrism* board3; // Third board in the porch
    Log* pLog1;               // Left side hand rail
    Log* pLog2;               // Front hand rail
    Log* pLog3;               // Right side hand rail
    Log* pLog4;               // Left side hand rail support
    Log* pLog5;               // Right side hand rail support
};

#endif
