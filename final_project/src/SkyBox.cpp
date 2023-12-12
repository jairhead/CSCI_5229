/*
 * File: SkyBox.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the RectangularPrism class, a child class
 *              of the BaseObject abstract class.
 */

#include "SkyBox.h"

// Default Constructor
SkyBox::SkyBox() {
  data = WeatherData::getInstance();
}

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

// setPartlyCloudy() public member function
// Sets the texture for the sides of the skybox for partly cloudy conditions
void SkyBox::setPartlyCloudyTexture(unsigned int* tex) {
  partlyCloudyTexture = tex;
  textureEnabled = true;
}

// draw() public member function
// Contains logic to draw the object
void SkyBox::draw() {
  // Disable lighting
  if (lightingEnabled) {glDisable(GL_LIGHTING);}

  // Save transformation; Translate -> Rotate -> Scale
  glPushMatrix();
  glTranslated(posArray[0], posArray[1], posArray[2]);
  glRotated(theta, 0, 1, 0);
  glScaled(scaleArray[0], scaleArray[1], scaleArray[2]);
  glColor3f(colorArray[0], colorArray[1], colorArray[2]);

  // Get weather condition
  char weatherCondition = data->getCurrentWeatherCondition();
  if (weatherCondition == 'p') {
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, *partlyCloudyTexture);
  }

  // Draw back side
  glBegin(GL_QUADS);
  if (weatherCondition == 'p') {glTexCoord2f(0, 0);} glVertex3f(-1, -1, -1);
  if (weatherCondition == 'p') {glTexCoord2f(1, 0);} glVertex3f(+1, -1, -1);
  if (weatherCondition == 'p') {glTexCoord2f(1, 1);} glVertex3f(+1, +1, -1);
  if (weatherCondition == 'p') {glTexCoord2f(0, 1);} glVertex3f(-1, +1, -1);

  // Draw right side
  if (weatherCondition == 'p') {glTexCoord2f(0, 0);} glVertex3f(+1, -1, -1);
  if (weatherCondition == 'p') {glTexCoord2f(0, 1);} glVertex3f(+1, -1, +1);
  if (weatherCondition == 'p') {glTexCoord2f(1, 1);} glVertex3f(+1, +1, +1);
  if (weatherCondition == 'p') {glTexCoord2f(1, 0);} glVertex3f(+1, +1, -1);

  // Draw front side
  if (weatherCondition == 'p') {glTexCoord2f(1, 0);} glVertex3f(+1, -1, +1);
  if (weatherCondition == 'p') {glTexCoord2f(0, 0);} glVertex3f(-1, -1, +1);
  if (weatherCondition == 'p') {glTexCoord2f(0, 1);} glVertex3f(-1, +1, +1);
  if (weatherCondition == 'p') {glTexCoord2f(1, 1);} glVertex3f(+1, +1, +1);

  // Draw left side
  if (weatherCondition == 'p') {glTexCoord2f(0, 1);} glVertex3f(-1, -1, +1);
  if (weatherCondition == 'p') {glTexCoord2f(0, 0);} glVertex3f(-1, -1, -1);
  if (weatherCondition == 'p') {glTexCoord2f(1, 0);} glVertex3f(-1, +1, -1);
  if (weatherCondition == 'p') {glTexCoord2f(1, 1);} glVertex3f(-1, +1, +1);
  glEnd();

  // Draw top
  glBegin(GL_QUADS);
  if (weatherCondition == 'p') {glTexCoord2f(1, 0);} glVertex3f(+1, +1, -1);
  if (weatherCondition == 'p') {glTexCoord2f(1, 1);} glVertex3f(+1, +1, +1);
  if (weatherCondition == 'p') {glTexCoord2f(0, 1);} glVertex3f(-1, +1, +1);
  if (weatherCondition == 'p') {glTexCoord2f(0, 0);} glVertex3f(-1, +1, -1);
  glEnd();

  // End
  if (weatherCondition == 'p') {glDisable(GL_TEXTURE_2D);}
  glPopMatrix();
}
