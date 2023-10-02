/*
 * File: ProjectionManager.h
 * Author: Jared McKneely
 * Description: Header file for the ProjectionManager class
 */

#include <iostream>
#include "GlutIncludes.h"

class ProjectionManager {
  public:
    ProjectionManager();
    ~ProjectionManager();
    void setTheta(double th);
    void setPhi(double ph);
    void setDimension(double dim);
    void setAspectRatio(double asp);
    void setFieldOfView(double fovy);
    void setClippingDistanceFactor(double cdf);
    double getTheta();
    double getPhi();
    double getDimension();
    double getAspectRatio();
    double getFieldOfView();
    double getClippingDistanceFactor();
    void setOrthogonal();
    void setProjection();
    void setLookAt();
    void setFirstPerson();
  private:
    double theta = 0.0;
    double phi = 0.0;
    double dimension = 1.0;
    double aspectRatio = 5.0;
    double orthoCorrection = 0.25;
    double fieldOfViewY = 90.0;
    double clipDistFactor = 10.0;
    double clipCorrection = 4.0;
    double lookAtCorrection = 2.5;
    double sine(double angle);
    double cosine(double angle);
};
