/*
 * File: Cabin.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the Cabin class, a child
 *              class of the BaseObject abstract class.
 */

#include "Cabin.h"

// Constructor
Cabin::Cabin() {
  // Get pointer to data structure
  data = WeatherData::getInstance();

  // Initialize logs
  log = new Log();
}

// Destructor
Cabin::~Cabin() { }

// setTextureFactor() public member function
// Sets the texture factor (scaling) for the cabin
void Cabin::setTextureFactor(float tf) {texFact = tf;}

// setLogCircularTexture() public overloaded member function
// Sets the texture of the log's circumference
void Cabin::setLogCircularTexture(unsigned int *tex) {
  logCircularTexture = tex;
  textureEnabled = true;
}

// setLogTopTexture() public overloaded member function
// Sets the texture of the log's ends
void Cabin::setLogTopTexture(unsigned int *tex) {
  logTopTexture = tex;
  textureEnabled = true;
}

// draw() public member function
// Contains logic to draw the object
void Cabin::draw() {
  // Set lighting properties
  if (lightingEnabled) {
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shinyFactor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularArray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissionArray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseArray);
  }

  // Save transformation; Translate -> Rotate -> Scale
  glPushMatrix();
  glTranslated(posArray[0], posArray[1], posArray[2]);
  glRotated(theta, 0, 1, 0);
  glScaled(scaleArray[0], scaleArray[1], scaleArray[2]);
  glColor3f(colorArray[0], colorArray[1], colorArray[2]);

  // Draw the cabin
  log->setPhi(270.0);
  log->setLogCircularTexture(logCircularTexture);
  log->setLogTopTexture(logTopTexture);
  log->draw();

  // End
  glPopMatrix();
  if (textureEnabled) {glDisable(GL_TEXTURE_2D);}
}

// drawPatio() private member function
// Contains logic to draw the patio of the cabin
void Cabin::drawPatio() {

}

// drawLog() private member function
// Contains logic to draw a log on the cabin
void Cabin::drawLog(double x1, double x2,
                    double y1, double y2,
                    double z1, double z2,
                    double ph) {

}
