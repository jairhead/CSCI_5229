/*
 * File: ProjectionManager.h
 * Author: Jared McKneely
 * Description: Header file for the ProjectionManager class
 */

#include <iostream>
#include <math.h>

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

class ProjectionManager {
  public:
    ProjectionManager();
    ~ProjectionManager();
    void setDimension(double dim);
    void setAspectRatio(double asp);
    void setFieldOfView(double fovy);
    void setClippingDistanceFactor(double cdf);
    double getDimension();
    double getAspectRatio();
    double getFieldOfView();
    double getClippingDistanceFactor();
    void setOrthogonal();
    void setProjection(double th, double ph);
    void setFirstPerson();
  private:
    double dimension = 1.0;
    double aspectRatio = 5.0;
    double fieldOfViewY = 55.0;
    double clipDistFactor = 10.0;
    double sine(double angle);
    double cosine(double angle);
};
