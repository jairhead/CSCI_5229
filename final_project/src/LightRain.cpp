/*
 * File: LightRain.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the LightRain class, a child class
 *              of the BaseWeatherCondition abstract class.
 */

#include "LightRain.h"

// Default Constructor
LightRain::LightRain() {
  sky = new SkyBox();
}

// Destructor
LightRain::~LightRain() { }

// draw() public member function
// Contains logic to draw the weather condition
void LightRain::draw() {
  // Set lighting properties
  if (lightingEnabled) { }

  // Save transformation and set up; Translate -> Rotate -> Scale
  glPushMatrix();
  glTranslated(posArray[0], posArray[1], posArray[2]);
  glRotated(theta, 0, 1, 0);
  glScaled(scaleArray[0], scaleArray[1], scaleArray[2]);

  // Draw sky
  sky->color(0.0,0.24,0.76);
  sky->scale(3.0, 3.0, 3.0);
  sky->draw();

  // End
  glEnd();
  glPopMatrix();
}
