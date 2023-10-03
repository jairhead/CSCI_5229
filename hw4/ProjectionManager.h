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
    void setFirstPerson();
    void moveForward();
    void moveBackward();
    void turnRight();
    void turnLeft();
  private:
    // Ortho and Projection Variables
    double theta = 0.0;
    double phi = 0.0;
    double dimension = 1.0;
    double aspectRatio = 5.0;
    double orthoCorrection = 0.25;
    double fieldOfViewY = 90.0;
    double clipDistFactor = 10.0;
    double clipCorrection = 10.0;
    double lookAtCorrection = 2.5;

    // First Person Navigation Variables
    double fpHeight = 0.1;
    double fpXPos = 0.01;
    double fpZPos = 0.01;
    double fpCx = 0.02;
    double fpCz = 0.02;
    double fpTheta = 45.0;
    double movementSpeed = 0.01;
    double turnSpeed = 1.0;

    // Angle Computations
    double sine(double angle);
    double cosine(double angle);
    double tangent(double angle);
};
