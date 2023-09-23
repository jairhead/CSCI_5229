/*
 * File: BaseObject.h
 * Author: Jared McKneely
 * Description: Header file for the BaseObject class, an abstract
 *              class used for 3D objects.
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

 class BaseObject {
  public:
    void setX(double x) {xPos = x;}
    void setY(double y) {yPos = y;}
    void setZ(double z) {zPos = z;}
    double getX() {return xPos;}
    double getY() {return yPos;}
    double getZ() {return zPos;}
    virtual void draw();
  protected:
    double xPos = 0.0;
    double yPos = 0.0;
    double zPos = 0.0;
 };
