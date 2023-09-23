/*
 * File: Cube.h
 * Author: Jared McKneely
 * Description: Header file for the Cube class
 */

#include <iostream>

// OpenGL with prototypes for glext
#ifdef USEGLEW
#include <GL/glew.h>
#endif

// Include glut header
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#else
#include <GL/glut.h>
#endif

// Default resolution
#ifndef RES
#define RES 1
#endif

class Cube {
  public:
    Cube(double x, double y, double z, double th);
    ~Cube();
    void display();
};
