/*
 * File: LorenzAttractorHelper.h
 * Description: Header file for the LorenzAttractorHelper object
 */

#include <stdio.h>
#include <iostream>

// OpenGL with prototypes for glext
#ifdef USEGLEW
#include <GL/glew.h>
#endif

// Include glut header
#define GL_GLEXT_PROTOTYPES
#ifdef _APPLE_
#include <GLUT/glut.h>
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#else
#include <GL/glut.h>
#endif

// Default resolution
#ifndef RES
#define RES 1
#endif

class LorenzAttractorHelper {
  public:
    LorenzAttractorHelper();
    ~LorenzAttractorHelper();
    void helloWorld();
  private:
    // Lorenz Parameters
    const double s  = 10;
    const double b  = 2.6666;
    const double r  = 28;

};
