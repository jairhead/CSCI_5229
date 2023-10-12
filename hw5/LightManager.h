/*
 * File: LightManager.h
 * Author: Jared McKneely
 * Description: Header file for the LightManager class
 */

#include <iostream>
#include "GlutIncludes.h"
#include "Sphere.h"

class LightManager {
  public:
    LightManager();
    ~LightManager();
    void init();
    void setDrawLight(bool draw);
    void setAmbient(int intensity);
    void setDiffuse(int intensity);
    void setSpecular(int intensity);
    bool getDrawLight();
    int getAmbient();
    int getDiffuse();
    int getSpecular();
    void translateLight0(double x, double y, double z);
    void enableLight0();
  private:
    // Lighting parameters
    int ambIntensity = 1;   // % intensity of ambient light
    int diffIntensity = 60; // % intensity of diffuse light
    int specIntensity = 60; // % intensity of specular light
    int localViewer = 1;    // Model for local viewer
    float w = 1.0;          // w value for homogeneous coordinates
    float n = 0.01;         // Normalization factor
    bool drawLight = true;  // Draw a little ball at the light's position
    Sphere *light0Ball;     // Little ball at light's position

    // Light positions
    float posArray[3] = {0.0, 0.0, 0.0};    
};
