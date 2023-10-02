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
  glOrtho((-aspectRatio * dimension), (aspectRatio * dimension), -dimension, dimension, -dimension, dimension);

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
  gluPerspective(fieldOfViewY, aspectRatio, (dimension / clipDistFactor), (dimension * clipDistFactor));

  // Set back to model view, undo previous transforms
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

// setFirstPerson
// Sets up a first person view
void ProjectionManager::setFirstPerson() { }