/*
 * File: SkyBox.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the RectangularPrism class, a child class
 *              of the BaseObject abstract class.
 */

#include "SkyBox.h"

// Default Constructor
SkyBox::SkyBox() { }

// Destructor
SkyBox::~SkyBox() { }

// color() public member function
// Sets the object's color values
void SkyBox::color(float r, float g, float b) {
  colorArray[0] = r;
  colorArray[1] = g;
  colorArray[2] = b;
}

// setTextureFactor() public member function
// Sets the texture factor (scaling) for the object
void SkyBox::setTextureFactor(float tf) {texFact = tf;}

// setSkySideTexture() public member function
// Sets the texture for the sides of the skybox
void SkyBox::setSkySideTexture(unsigned int* tex) {
  skySideTexture = tex;
  textureEnabled = true;
}

// setSkyTopTexture() public member function
// Sets the texture for the top of the skybox
void SkyBox::setSkyTopTexture(unsigned int* tex) {
  skyTopTexture = tex;
  textureEnabled = true;
}

// draw() public member function
// Contains logic to draw the object
void SkyBox::draw() {
  // Disable lighting
  if (lightingEnabled) {glDisable(GL_LIGHTING);}

  // Set texture properties
  if (textureEnabled) {
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  }

  // Save transformation; Translate -> Rotate -> Scale
  glPushMatrix();
  glTranslated(posArray[0], posArray[1], posArray[2]);
  glRotated(theta, 0, 1, 0);
  glScaled(scaleArray[0], scaleArray[1], scaleArray[2]);
  glColor3f(colorArray[0], colorArray[1], colorArray[2]);

  // Draw back side
  glBegin(GL_QUADS);
  if (textureEnabled) {glBindTexture(GL_TEXTURE_2D, *skySideTexture);}
  if (textureEnabled) {glTexCoord2f(0.00, 0);} glVertex3f(-1, -1, -1);
  if (textureEnabled) {glTexCoord2f(0.25, 0);} glVertex3f(+1, -1, -1);
  if (textureEnabled) {glTexCoord2f(0.25, 1);} glVertex3f(+1, +1, -1);
  if (textureEnabled) {glTexCoord2f(0.00, 1);} glVertex3f(-1, +1, -1);

  // Draw right side
  if (textureEnabled) {glTexCoord2f(0.25, 0);} glVertex3f(+1, -1, -1);
  if (textureEnabled) {glTexCoord2f(0.50, 0);} glVertex3f(+1, -1, +1);
  if (textureEnabled) {glTexCoord2f(0.50, 1);} glVertex3f(+1, +1, +1);
  if (textureEnabled) {glTexCoord2f(0.25, 1);} glVertex3f(+1, +1, -1);

  // Draw front side
  if (textureEnabled) {glTexCoord2f(0.50, 0);} glVertex3f(+1, -1, +1);
  if (textureEnabled) {glTexCoord2f(0.75, 0);} glVertex3f(-1, -1, +1);
  if (textureEnabled) {glTexCoord2f(0.75, 1);} glVertex3f(-1, +1, +1);
  if (textureEnabled) {glTexCoord2f(0.50, 1);} glVertex3f(+1, +1, +1);

  // Draw left side
  if (textureEnabled) {glTexCoord2f(0.75, 0);} glVertex3f(-1, -1, +1);
  if (textureEnabled) {glTexCoord2f(1.00, 0);} glVertex3f(-1, -1, -1);
  if (textureEnabled) {glTexCoord2f(1.00, 1);} glVertex3f(-1, +1, -1);
  if (textureEnabled) {glTexCoord2f(0.75, 1);} glVertex3f(-1, +1, +1);
  glEnd();

  // Draw top
  glBegin(GL_QUADS);
  if (textureEnabled) {glBindTexture(GL_TEXTURE_2D, *skySideTexture);}
  if (textureEnabled) {glTexCoord2f(0.00, 0);} glVertex3f(+1, +1, -1);
  if (textureEnabled) {glTexCoord2f(0.50, 0);} glVertex3f(+1, +1, +1);
  if (textureEnabled) {glTexCoord2f(0.50, 1);} glVertex3f(-1, +1, +1);
  if (textureEnabled) {glTexCoord2f(0.00, 1);} glVertex3f(-1, +1, -1);
  glEnd();

  // End
  if (textureEnabled) {glDisable(GL_TEXTURE_2D);}
  glPopMatrix();
}
