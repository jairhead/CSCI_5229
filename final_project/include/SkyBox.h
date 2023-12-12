/*
 * File: SkyBox.h
 * Author: Jared McKneely
 * Description: Header file for the RectangularPrism class
 */

#ifndef _SKY_BOX_H
#define _SKY_BOX_H

#include "BaseObject.h"
#include "WeatherData.h"

class SkyBox : public BaseObject {
  public:
    SkyBox();
    ~SkyBox();
    void color(float r, float g, float b);
    void setTextureFactor(float tf);
    void setPartlyCloudyTexture(unsigned int *tex);
    void draw();
  protected:
    // Color & lighting variables
    float colorArray[4] = {1.0, 1.0, 1.0, 1.0};
    float specularArray[4] = {1.0, 1.0, 1.0, 1.0};
    float emissionArray[4] = {0.0, 0.0, 0.0, 1.0};

    // Texture variables
    float texFact = 1.0;
    unsigned int *partlyCloudyTexture = nullptr;

    // Objects
    WeatherData* data = nullptr;
};

#endif
