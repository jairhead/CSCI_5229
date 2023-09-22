/*
 * File: PrimaryGraphicsHelper.h
 * Author: Jared McKneely
 * Description: Header file for the PrimaryGraphicsHelper class
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

class PrimaryGraphicsHelper {
  public:
    PrimaryGraphicsHelper();
    ~PrimaryGraphicsHelper();
    static void display();
    static void reshape(int w, int h);
    static void special(int key, int x, int y);
    static void key(unsigned char ch, int x, int y);
    static void initializeGlew();
};
