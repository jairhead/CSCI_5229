/*
 * File: LightManager.cpp
 * Author: Jared McKneely
 * Description: Implementation file for LightManager, a helper class
 *              used for managing light sources within OpenGL.
 */

#include "LightManager.h"

// Constructor
LightManager::LightManager() {init();}

// Destructor
LightManager::~LightManager() { }

// init() public member function
// Enables and initializes lighting mode
void LightManager::init() {
  // Enable normalized normal vectors
  glEnable(GL_NORMALIZE);

  // Enable lighting mode, configure lighting model parameters for colors
  glEnable(GL_LIGHTING);
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, localViewer);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
}

// enableLight0() public member function
// Enables GL_LIGHT0 in OpenGL
void LightManager::enableLight0() {
  // Set up ambient, diffuse, and specular lighting parameters
  float amb[] = {(n * ambIntensity), (n * ambIntensity), (n * ambIntensity), w}; 
  float diff[] = {(n * diffIntensity), (n * diffIntensity), (n * diffIntensity), w}; 
  float spec[] = {(n * specIntensity), (n * specIntensity), (n * specIntensity), w};

  // Enable light soure 0
  glEnable(GL_LIGHT0);

  // Set ambient, diffuse, and specular light
  glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
  glLightfv(GL_LIGHT0, GL_SPECULAR, spec);

  // Set position of light 0
  glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);
}
