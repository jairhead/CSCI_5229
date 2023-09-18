/*
 * File: LorenzAttractorHelper.h
 * Author: Jared McKneely
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
    static void display();
    static void reshape(int w, int h);
    static void special(int key, int x, int y);
    static void key(unsigned char ch, int x, int y);
    static void printLorenzAttractorParameters();
  private:
    static void computeEulerStep(double &x, double &y, double &z);
    static void displayText(std::string text);
    static void createAxes();
    static void createLorenzAttractor(double x, double y, double z);
    static void errorCheck(std::string where);
};
