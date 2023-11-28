/*
 * File: ProjectionManager.cpp
 * Author: Jared McKneely
 * Description: Implementation file for ProjectionNanager, a helper class
 *              used for managing the projection within OpenGL.
 */

#include "ProjectionManager.h"

// Constructor
ProjectionManager::ProjectionManager() { }

// Destructor
ProjectionManager::~ProjectionManager() { }

// Theta Setter
void ProjectionManager::setTheta(double th) {
  if (th < 0) {th = 359;}
  else if (th > 360) {th = 0;}
  theta = th;
}

// Phi Setter
void ProjectionManager::setPhi(double ph) {
  if (ph < 0) {ph = 359;}
  else if (ph > 360) {ph = 0;}
  phi = ph;
}

// Dimension Setter
void ProjectionManager::setDimension(double dim) {dimension = dim;}

// Aspect Ratio Setter
void ProjectionManager::setAspectRatio(double asp) {aspectRatio = asp;}

// Field of View Setter
void ProjectionManager::setFieldOfView(double fovy) {fieldOfViewY = fovy;}

// Clipping Distance Factor Setter
void ProjectionManager::setClippingDistanceFactor(double cdf) {clipDistFactor = cdf;}

// Theta Getter
double ProjectionManager::getTheta() {return theta;}

// Phi Getter
double ProjectionManager::getPhi() {return phi;}

// Dimension Getter
double ProjectionManager::getDimension() {return dimension;}

// Aspect Ratio Getter
double ProjectionManager::getAspectRatio() {return aspectRatio;}

// Field of View Getter
double ProjectionManager::getFieldOfView() {return fieldOfViewY;}

// Clipping Distance Factor Setter
double ProjectionManager::getClippingDistanceFactor() {return clipDistFactor;}

// setOrthogonal
// Multiplies the projection matrix with an orthogonal matrix
void ProjectionManager::setOrthogonal() {
  // Modify projection matrix, undo previous transforms
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Multiply by orthographic matrix
  glOrtho((-aspectRatio * dimension) - orthoCorrection,
          (aspectRatio * dimension) + orthoCorrection,
          (-dimension - orthoCorrection),
          (dimension + orthoCorrection),
          (-clipCorrection * dimension),
          (clipCorrection * dimension));

  // Rotate
  glRotated(phi, 1, 0, 0);
  glRotated(theta, 0, 1, 0);

  // Set back to model view, undo previous transforms
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

// setProjection
// Sets up a projection
void ProjectionManager::setProjection() {
  // Modify projection matrix, undo previous transforms
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Multiply by a projection matrix
  gluPerspective(fieldOfViewY, aspectRatio,
                 (dimension / clipDistFactor),
                 (dimension * clipDistFactor));

  // Call gluLookAt()
  double Ex = (-lookAtCorrection * dimension * Utilities::sine(theta) * Utilities::cosine(phi));
  double Ey = (lookAtCorrection * dimension * Utilities::sine(phi));
  double Ez = (lookAtCorrection * dimension * Utilities::cosine(theta) * Utilities::cosine(phi));
  gluLookAt(Ex, Ey, Ez, 0.0, 0.0, 0.0, 0.0, Utilities::cosine(phi), 0.0);

  // Set back to model view, undo previous transforms
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

// setFirstPerson
// Sets up a first person view
void ProjectionManager::setFirstPerson() {
 // Modify projection matrix, undo previous transforms
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Multiply by a projection matrix
  gluPerspective(fieldOfViewY, aspectRatio,
                 (dimension / (clipDistFactor * 10.0)),
                 (dimension * (clipDistFactor * 10.0)));

  // Call gluLookAt()
  gluLookAt(fpXPos, fpYPos, fpZPos, fpCx, fpCy, fpCz, 0.0, Utilities::cosine(fpPhi), 0.0);

  // Set back to model view, undo previous transforms
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

// moveForward
// Moves the first person character forward
void ProjectionManager::moveForward() {
  fpXPos += (movementSpeed * Utilities::cosine(fpTheta));
  fpZPos += (movementSpeed * Utilities::sine(fpTheta));
  fpCx += (movementSpeed * Utilities::cosine(fpTheta) * Utilities::cosine(fpPhi));
  fpCz += (movementSpeed * Utilities::sine(fpTheta) * Utilities::cosine(fpPhi));
  checkPosition();
}

// moveBackward
// Moves the first person character backward
void ProjectionManager::moveBackward() {
  fpXPos -= (movementSpeed * Utilities::cosine(fpTheta));
  fpZPos -= (movementSpeed * Utilities::sine(fpTheta));
  fpCx -= (movementSpeed * Utilities::cosine(fpTheta));
  fpCz -= (movementSpeed * Utilities::sine(fpTheta));
  checkPosition();
}

// moveRight
// Moves the first person character to the right
void ProjectionManager::moveRight() {
  fpXPos += (movementSpeed * Utilities::cosine(fpTheta + 90.0));
  fpZPos += (movementSpeed * Utilities::sine(fpTheta + 90.0));
  fpCx += (movementSpeed * Utilities::cosine(fpTheta + 90.0));
  fpCz += (movementSpeed * Utilities::sine(fpTheta + 90.0));
  checkPosition();
}

// moveLeft
// Moves the first person character to the left
void ProjectionManager::moveLeft() {
  fpXPos -= (movementSpeed * Utilities::cosine(fpTheta + 90.0));
  fpZPos -= (movementSpeed * Utilities::sine(fpTheta + 90.0));
  fpCx -= (movementSpeed * Utilities::cosine(fpTheta + 90.0));
  fpCz -= (movementSpeed * Utilities::sine(fpTheta + 90.0));
  checkPosition();
}

// turnRight
// Rotates the first person character to the right
void ProjectionManager::turnRight() {
  fpTheta += turnSpeed;
  fpCx = fpXPos + (turnSpeed * Utilities::cosine(fpTheta));
  fpCz = fpZPos + (turnSpeed * Utilities::sine(fpTheta));
}

// turnLeft
// Rotates the first person character to the left
void ProjectionManager::turnLeft() {
  fpTheta -= turnSpeed;
  fpCx = fpXPos + (turnSpeed * Utilities::cosine(fpTheta));
  fpCz = fpZPos + (turnSpeed * Utilities::sine(fpTheta));
}

// lookUp
// Rotates the first person character's head upward
void ProjectionManager::lookUp() {
  fpCy += 0.001;
}

// lookDown
// Rotates the first person character's head downward
void ProjectionManager::lookDown() {
  fpCy -= 0.001;
}

// getFirstPersonTheta
// Sets the first person character's rotation
double ProjectionManager::getFirstPersonTheta() {
  return fpTheta;
}

// setFirstPersonX
// Sets the first person x position
void ProjectionManager::setFirstPersonX(double val) {
  fpXPos = val;
}

// setFirstPersonY
// Returns the first person y position
void ProjectionManager::setFirstPersonY(double val) {
  fpYPos = val;
}

// setFirstPersonZ
// Sets the first person z position
void ProjectionManager::setFirstPersonZ(double val) {
  fpZPos = val;
}

// getFirstPersonX
// Returns the first person x position
double ProjectionManager::getFirstPersonX() {
  return fpXPos;
}

// getFirstPersonY
// Returns the first person y position
double ProjectionManager::getFirstPersonY() {
  return fpYPos;
}

// getFirstPersonZ
// Returns the first person z position
double ProjectionManager::getFirstPersonZ() {
  return fpZPos;
}

// checkPosition private member function
// Ensures that fpXPos and fpZPos are between the min and max for first person
void ProjectionManager::checkPosition() {
  if (fpXPos > fpXMax) {fpXPos = fpXMax;}
  if (fpXPos < fpXMin) {fpXPos = fpXMin;}
  if (fpZPos > fpZMax) {fpZPos = fpZMax;}
  if (fpZPos < fpZMin) {fpZPos = fpZMin;}
}

// checkHeadAngle private member function
// Ensures that fpPhi is never greater than fpPhiMax nor lesser than fpPhiMin
void ProjectionManager::checkHeadAngle() {
  if (fpPhi > fpPhiMax) {fpPhi = fpPhiMax;}
  if (fpPhi > fpPhiMax) {fpPhi = fpPhiMax;}
}
