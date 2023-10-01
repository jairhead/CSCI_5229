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
    void setOrthogonal();
    void setDimension(double dim);
    void setAspectRatio(double asp);
    void setFieldOfView(double fov);
    double getDimension();
    double getAspectRatio();
    double getFieldOfView();
  private:
    double dimension = 2.0;
    double aspectRatio = 1.0;
    double fieldOfView = 1.0;
};
