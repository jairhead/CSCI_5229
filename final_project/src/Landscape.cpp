/*
 * File: Landscape.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the Landscape class, a child class
 *              of the BaseObject abstract class.
 */

#include "Landscape.h"

// Default Constructor
Landscape::Landscape() {
  // Get pointer to data structure
  data = WeatherData::getInstance();

  // Load .obj files
  grassValley = Utilities::loadOBJ("data/hillyGrassValley.obj");
  mountainRim = Utilities::loadOBJ("data/mountainRim.obj");
  mountainSnow = Utilities::loadOBJ("data/mountainSnow.obj");

  // Instantiate clock face
  clock = new AnalogClock();
  clock->enableLighting();
}

// Destructor
Landscape::~Landscape() {
  delete clock;
}

// color() public member function
// Sets the object's color values
void Landscape::color(float r, float g, float b) {
  colorArray[0] = r;
  colorArray[1] = g;
  colorArray[2] = b;
}

// setTextureFactor() public member function
// Sets the texture factor (scaling) for the object
void Landscape::setTextureFactor(float tf) {texFact = tf;}

// draw() public member function
// Contains logic to draw the object
void Landscape::draw() {
  // Set lighting properties
  if (lightingEnabled) {
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shinyFactor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colorArray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorArray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularArray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissionArray);
  }
  glEnable(GL_LIGHTING);

  // Save transformation; Translate -> Rotate -> Scale
  glPushMatrix();
  glTranslated(posArray[0], posArray[1], posArray[2]);
  glRotated(theta, 0, 1, 0);
  glScaled(scaleArray[0], scaleArray[1], scaleArray[2]);

  // Draw the grass landscape using elevation data
  char weatherCondition = data->getCurrentWeatherCondition();
  if (weatherCondition == 's') {glColor3f(0.95, 0.95, 0.95);}
  else {glColor3f(0.04, 0.33, 0);}
  glCallList(grassValley);

  // Draw the mountains
  glTranslated(0.0, -0.1, 0.0);
  if (weatherCondition == 's') {glColor3f(0.95, 0.95, 0.95);}
  else {glColor3f(0.21, 0.21, 0.21);}
  glCallList(mountainRim);

  // Draw the mountain snow
  if (weatherCondition == 'n' || weatherCondition == 'r' || weatherCondition == 't') {glColor3f(0.21, 0.21, 0.21);}
  else {glColor3f(1.0, 1.0, 1.0);}
  glTranslated(0.0, -0.1, 0.0);
  glCallList(mountainSnow);

  // Draw the clock pole
  clock->translate(2.3, 1.1, 7.7);
  clock->scale(0.25, 0.25, 0.25);
  clock->draw();

  // End
  glPopMatrix();
}