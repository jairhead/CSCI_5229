/*
 * File: LightManager.h
 * Author: Jared McKneely
 * Description: Header file for the LightManager class
 */

#include <iostream>
#include "GlutIncludes.h"

class LightManager {
  public:
    LightManager();
    ~LightManager();
    void init();
    void enableLight0();
  private:
    // Lighting parameters
    int ambIntensity = 10;  // % intensity of ambient light
    int diffIntensity = 50; // % intensity of diffuse light
    int specIntensity = 10; // % intensity of specular light
    int localViewer = 1;    // Model for local viewer
    float w = 1.0;          // w value for homogeneous coordinates
    float n = 0.01;         // Normalization factor

    // Light positions
    float light0Pos[3] = {1.0, 0.0, 0.0};    
};
