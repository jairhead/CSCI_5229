/*
 * File: ProjectionManager.h
 * Author: Jared McKneely
 * Description: Header file for the ProjectionManager class
 */

#include <iostream>

#include "GlutIncludes.h"

class ProjectionManager {
  public:
    // Constructor & Destructor
    ProjectionManager();
    ~ProjectionManager();

    // Getters & Setters
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

    // View Setters
    void setOrthogonal();
    void setProjection();
    void setFirstPerson();

    // First Person Navigation
    void moveForward();
    void moveBackward();
    void moveRight();
    void moveLeft();
    void turnRight();
    void turnLeft();
    void lookUp();
    void lookDown();
    double getFirstPersonTheta();
    double getFirstPersonX();
    double getFirstPersonY();
    double getFirstPersonZ();
  private:
    // Ortho & Projection Variables
    double theta = 0.0;
    double phi = 0.0;
    double dimension = 1.0;
    double aspectRatio = 5.0;
    double orthoCorrection = 0.25;
    double fieldOfViewY = 90.0;
    double clipDistFactor = 10.0;
    double clipCorrection = 10.0;
    double lookAtCorrection = 2.5;

    // First Person Position Variables
    double movementSpeed = 0.01;
    double fpXPos = 0.01;
    double fpYPos = 0.1;
    double fpZPos = 0.01;
    double fpCx = 0.02;
    double fpCy = 0.1;
    double fpCz = 0.02;
    double fpXMax = 0.8;
    double fpXMin = -0.8;
    double fpZMax = 0.8;
    double fpZMin = -0.8;

    // First Person Angle Variables
    double turnSpeed = 1.0;
    double fpTheta = 45.0;
    double fpPhi = 0.0;
    double fpPhiMax = 90.0;
    double fpPhiMin = -90.0;

    // Private Member Functions
    double sine(double angle);
    double cosine(double angle);
    void checkPosition();
    void checkHeadAngle();
};
