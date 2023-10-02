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

// Dimension Setter
void ProjectionManager::setDimension(double dim) {dimension = dim;}

// Aspect Ratio Setter
void ProjectionManager::setAspectRatio(double asp) {aspectRatio = asp;}

// Field of View Setter
void ProjectionManager::setFieldOfView(double fovy) {fieldOfViewY = fovy;}

// Clipping Distance Factor Setter
void ProjectionManager::setClippingDistanceFactor(double cdf) {clipDistFactor = cdf;}

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
  glOrtho((-aspectRatio * dimension) - 0.25, (aspectRatio * dimension) + 0.25, -dimension - 0.25, dimension + 0.25, -dimension, 4 * dimension);

  // Set back to model view, undo previous transforms
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

// setProjection
// Sets up a projection
void ProjectionManager::setProjection(double th, double ph) {
  // Modify projection matrix, undo previous transforms
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Multiply by a projection matrix
  gluPerspective(fieldOfViewY, aspectRatio, (dimension / clipDistFactor), (dimension * clipDistFactor));

  // TODO: fix Ex, Ey, and Ez in this call
  double Ex = (dimension * sine(th) * cosine(ph));
  double Ey = (dimension * sine(th));
  double Ez = (dimension * cosine(th) * cosine(ph));
  gluLookAt(Ex, Ey, Ez, 0.0, 0.0, 0.0, 0.0, cosine(ph), 0.0);

  // Set back to model view, undo previous transforms
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

// setFirstPerson
// Sets up a first person view
void ProjectionManager::setFirstPerson() { }

// sine() private member function
// Returns the sine of the provided angle in degrees
double ProjectionManager::sine(double angle) {return sin(angle * (3.14159265 / 180));}

// cosine() private member function
// Returns the cosine of the provided angle in degrees
double ProjectionManager::cosine(double angle) {return cos(angle * (3.14159265 / 180));}
