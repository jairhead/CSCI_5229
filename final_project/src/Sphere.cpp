/*
 * File: Sphere.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the Sphere class, a child class
 *              of the BaseObject abstract class.
 */

#include "Sphere.h"

// Default Constructor
Sphere::Sphere() { }

// Destructor
Sphere::~Sphere() { }

// color() public member function
// Sets the object's colors
void Sphere::color(float r, float g, float b) {
  colorArray[0] = r;
  colorArray[1] = g;
  colorArray[2] = b;
}

// setSpecular() public member function
// Sets the specular light attributes
void Sphere::setSpecular(float r, float g, float b) {
  specularArray[0] = r;
  specularArray[1] = g;
  specularArray[2] = b;
}

// setEmission() public member function
// Sets the emission light attributes
void Sphere::setEmission(float r, float g, float b) {
  emissionArray[0] = r;
  emissionArray[1] = g;
  emissionArray[2] = b;
}

// setTextureFactor() public member function
// Sets the texture factor (scaling) for the sphere
void Sphere::setTextureFactor(float tf) {texFact = tf;}

// draw() member function
// Contains to display the sphere
void Sphere::draw() {
  // Set material properties
  if (lightingEnabled) {
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shinyFactor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularArray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissionArray);
  }

  // Set texture properties
  if (textureEnabled) {
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, *texture);
  }

  // Save transformation and set up; translate -> scale (no rotation)
  glPushMatrix();
  glTranslated(posArray[0], posArray[1], posArray[2]);
  glScaled(scaleArray[0], scaleArray[1], scaleArray[2]);
  glColor3f(colorArray[0], colorArray[1], colorArray[2]);

  // Draw the sphere
  for (int phi = -90; phi < 90; phi += increment) {
    glBegin(GL_QUAD_STRIP);
    for (int theta = 0; theta <= 360; theta += (2 * increment)) {
      // Draw bottom left vertex
      if (textureEnabled) {glTexCoord2f(0, 0);}
      vertex(theta, phi);

      // Draw top left vertex
      if (textureEnabled) {glTexCoord2f(0, texFact);}
      vertex(theta, phi + increment);

      // Draw bottom right vertex
      if (textureEnabled) {glTexCoord2f(texFact, 0);}
      vertex(theta + 2 * increment, phi);

      // Draw top right vertex
      if (textureEnabled) {glTexCoord2f(texFact, texFact);}
      vertex(theta + 2 * increment, phi + increment);
    }
    glEnd();
  }

  // End
  glPopMatrix();
  if (textureEnabled) {glDisable(GL_TEXTURE_2D);}
}

// vertex() private member function
// Draws a triangle with th and ph
void Sphere::vertex(double th, double ph) {
  double xVal = (Utilities::sine(th) * Utilities::cosine(ph)); 
  double yVal = (Utilities::cosine(th) * Utilities::cosine(ph));
  double zVal = Utilities::sine(ph);
  if (lightingEnabled) {glNormal3d(xVal, yVal, zVal);}
  glVertex3d(xVal, yVal, zVal);
}
