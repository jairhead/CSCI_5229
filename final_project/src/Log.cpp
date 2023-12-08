/*
 * File: Log.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the Log class, a child
 *              class of the BaseObject abstract class.
 */

#include "Log.h"

// Constructor
Log::Log() { }

// Destructor
Log::~Log() { }

// setTextureFactor() public member function
// Sets the texture factor (scaling) for the log
void Log::setTextureFactor(float tf) {texFact = tf;}

// setLogCircularTexture() public overloaded member function
// Sets the texture of the log's circumference
void Log::setLogCircularTexture(unsigned int *tex) {
  logCircularTexture = tex;
  textureEnabled = true;
}

// setLogTopTexture() public overloaded member function
// Sets the texture of the log's ends
void Log::setLogTopTexture(unsigned int *tex) {
  logTopTexture = tex;
  textureEnabled = true;
}

// setTheta() public member function
// Sets the y rotation value theta
void Log::setTheta(double th) {theta = th;}

// setPhi() public member function
// Sets the x rotation value phi
void Log::setPhi(double ph) {phi = ph;}

// draw() public member function
// Contains logic to draw the object
void Log::draw() {
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
  glRotated(phi, 1, 0, 0);
  glScaled(scaleArray[0], scaleArray[1], scaleArray[2]);
  glColor3f(colorArray[0], colorArray[1], colorArray[2]);

  // Set log circular texture
  if (textureEnabled) {
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, *logCircularTexture);
  }

  // Draw log circumference
  double r = 0.10; double l = 0.5;
  drawCircumference(r, l);

  // Set log top texture
  if (textureEnabled) {
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, *logTopTexture);
  }

  // Draw log top and bottom
  drawTop(r, l);
  drawBottom(r);

  // End
  glPopMatrix();
  if (textureEnabled) {glDisable(GL_TEXTURE_2D);}
}

// drawCircumference() private member function
// Contains logic to draw the circumference of the log
void Log::drawCircumference(double r, double l) {
  glBegin(GL_QUAD_STRIP);
  for (int th = 0; th <= 360; th += d) {
    // Draw normal vector
    if (lightingEnabled) {
      glNormal3d(Utilities::cosine(th), 0.0, Utilities::sine(th));
    }

    // Draw bottom right vertex
    float texP1 = (th) / 360.0; float texP2 = (th + d) / 360.0;
    if (textureEnabled) {glTexCoord2f(texP1, 0.0);}
    glVertex3d(r * Utilities::cosine(th), 0.0, r * Utilities::sine(th));

    // Draw top right vertex
    if (textureEnabled) {glTexCoord2f(texP1, 1.0);}
    glVertex3d(r * Utilities::cosine(th), l, r * Utilities::sine(th));

    // Draw bottom left vertex
    if (textureEnabled) {glTexCoord2f(texP2, 0.0);}
    glVertex3d(r * Utilities::cosine(th + d), 0.0, r * Utilities::sine(th + d));

    // Draw top left vertex
    if (textureEnabled) {glTexCoord2f(texP2, 1.0);}
    glVertex3d(r * Utilities::cosine(th + d), l, r * Utilities::sine(th + d));
  }
  glEnd();
}

// drawTop() private member function
// Contains logic to draw the top of the log
void Log::drawTop(double r, double l) {
  for (int th = 0; th <= 360; th += d) {
    // Draw normal vector
    glBegin(GL_TRIANGLES);
    if (lightingEnabled) {glNormal3d(0.0, 1.0, 0.0);}

    // Draw middle vertex
    float texP1 = (th) / 360.0; float texP2 = (th + d) / 360.0;
    if (textureEnabled) {glTexCoord2f(texP1, 1.0);}
    glVertex3d(0.0, l, 0.0);

    // Draw outer right vertex
    if (textureEnabled) {glTexCoord2f(texP1, 0);}
    glVertex3d(r * Utilities::cosine(th), l, r * Utilities::sine(th));

    // Draw outer left vertex
    if (textureEnabled) {glTexCoord2f(texP2, 0);}
    glVertex3d(r * Utilities::cosine(th + d), l, r * Utilities::sine(th + d));
    glEnd();
  }
}

// drawBottom() private member function
// Contains logic to draw the bottom of the log
void Log::drawBottom(double r) {
  for (int th = 0; th <= 360; th += d) {
    // Draw normal vector
    glBegin(GL_TRIANGLES);
    if (lightingEnabled) {glNormal3d(0.0, -1.0, 0.0);}

    // Draw middle vertex
    float texP1 = (th) / 360.0; float texP2 = (th + d) / 360.0;
    if (textureEnabled) {glTexCoord2f(texP1, 1.0);}
    glVertex3d(0.0, 0.0, 0.0);

    // Draw outer right vertex
    if (textureEnabled) {glTexCoord2f(texP1, 0);}
    glVertex3d(r * Utilities::cosine(th), 0.0, r * Utilities::sine(th));

    // Draw outer left vertex
    if (textureEnabled) {glTexCoord2f(texP2, 0);}
    glVertex3d(r * Utilities::cosine(th + d), 0.0, r * Utilities::sine(th + d));
    glEnd();
  }
}
