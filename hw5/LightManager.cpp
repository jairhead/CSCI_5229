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

  // Instantiate light ball
  light0Ball = new Sphere();
  light0Ball->setEmission(0.7, 0.7, 0.7);
}

// setDrawLight() public member function
// Sets drawLight
void LightManager::setDrawLight(bool draw) {drawLight = draw;}

// translateLight0() public member function
// Move the position of GL_LIGHT0
void LightManager::translateLight0(double x, double y, double z) {
  posArray[0] = x;
  posArray[1] = y;
  posArray[2] = z;
}

// enableLight0() public member function
// Enables GL_LIGHT0 in OpenGL
void LightManager::enableLight0() {
  // Set up ambient, diffuse, and specular lighting parameters
  float amb[] = {(n * ambIntensity), (n * ambIntensity), (n * ambIntensity), w}; 
  float diff[] = {(n * diffIntensity), (n * diffIntensity), (n * diffIntensity), w}; 
  float spec[] = {(n * specIntensity), (n * specIntensity), (n * specIntensity), w};
  float pos[] = {posArray[0], posArray[1], posArray[2], 1.0};

  // Enable light soure 0
  glEnable(GL_LIGHT0);

  // Set ambient, diffuse, specular, and position of light
  glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
  glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
  glLightfv(GL_LIGHT0, GL_POSITION, pos);

  // Draw the light ball
  if (drawLight) {
    light0Ball->translate(pos[0], pos[1], pos[2]);
    light0Ball->scale(0.03, 0.03, 0.03);
    light0Ball->draw();
  }
}

