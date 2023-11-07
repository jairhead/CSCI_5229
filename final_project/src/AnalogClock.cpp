/*
 * File: AnalogClock.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the AnalogClock class, a child
 *              class of the BaseObject abstract class.
 */

#include "AnalogClock.h"

// Constructor
AnalogClock::AnalogClock() { }

// Destructor
AnalogClock::~AnalogClock() { }

// color() public member function
// Sets the object's color values
void AnalogClock::color(double r, double g, double b) {
  colorArray[0] = r;
  colorArray[1] = g;
  colorArray[2] = b;
  shinyFactor = 1.0;
}

// setTextureFactor() public member function
// Sets the texture factor (scaling) for the pawn
void AnalogClock::setTextureFactor(float tf) {texFact = tf;}

// setTexture() public overloaded member function
// Sets the texture of the pawn
void AnalogClock::setTexture(unsigned int *tex) {texture = tex;}

// draw() public member function
// Contains logic to draw the object
void AnalogClock::draw() {
  // Set lighting properties
  if (lightingEnabled) {
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shinyFactor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularArray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissionArray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseArray);
  }

  // Save transformation, Translate -> Rotate -> Scale
  glPushMatrix();
  glTranslated(posArray[0], posArray[1], posArray[2]);
  glRotated(theta, 0, 1, 0);
  glScaled(scaleArray[0], scaleArray[1], scaleArray[2]);
  
  // Draw the clock
  drawClockFace(0.1);
  drawClockRim(0.1);
  drawClockMarkers(0.1);
  drawHourHand(0.1);
  drawMinuteHand(0.1);

  // End
  glPopMatrix();
}

// drawClockFace() protected member function
// Contains logic to draw the clock face
void AnalogClock::drawClockFace(double y) {
  glColor3f(colorArray[0], colorArray[1], colorArray[2]);
  for (int th = 0; th <= 360; th += d) {
    // Draw normal vector
    glBegin(GL_TRIANGLES);
    if (lightingEnabled) {glNormal3d(0.0, y, 0.0);}

    // Draw middle vertex
    if (textureEnabled) {glTexCoord2f(texFact, texFact);}
    glVertex3d(0.0, y, 0.0);

    // Draw outer right vertex
    if (textureEnabled) {glTexCoord2f(texFact, 0);}
    glVertex3d(r * cosine(th), y, r * sine(th));

    // Draw outer left vertex
    if (textureEnabled) {glTexCoord2f(0, 0);}
    glVertex3d(r * cosine(th + d), y, r * sine(th + d));
    glEnd();
  }
}

// drawClockRim() protected member function
// Contains logic to draw the clock rim
void AnalogClock::drawClockRim(double y) {
  // Outside of clock rim
  glBegin(GL_QUAD_STRIP);
  glColor3f(0.54, 0.54, 0.54);
  for (int th = 0; th <= 360; th += d) {
    // Draw normal vector
    if (lightingEnabled) {glNormal3d(cosine(th), 0.0, sine(th));}

    // Draw bottom vertex
    if (textureEnabled) {glTexCoord2f(0, 0);}
    glVertex3d(r * cosine(th), y - 0.1, r * sine(th));

    // Draw top vertex
    if (textureEnabled) {glTexCoord2f(0, texFact);}
    glVertex3d(r * cosine(th), y + 0.1, r * sine(th));
  }
  glEnd();

  // Inside of clock rim
  glBegin(GL_QUAD_STRIP);
  for (int th = 0; th <= 360; th += d) {
    // Draw normal vector
    if (lightingEnabled) {glNormal3d(cosine(th + 180.0), 0.0, sine(th + 180.0));}

    // Draw bottom vertex
    if (textureEnabled) {glTexCoord2f(0, 0);}
    glVertex3d((r - 0.1) * cosine(th), y - 0.1, (r - 0.1) * sine(th));

    // Draw top vertex
    if (textureEnabled) {glTexCoord2f(0, texFact);}
    glVertex3d((r - 0.1) * cosine(th), y + 0.1, (r - 0.1) * sine(th));
  }
  glEnd();

  // Top of clock rim
  glBegin(GL_QUAD_STRIP);
  for (int th = 0; th <= 360; th += d) {
    // Draw normal vector
    if (lightingEnabled) {glNormal3d(0.0, 1.0, 0.0);}

    // Draw inner vertex
    if (textureEnabled) {glTexCoord2f(0, 0);}
    glVertex3d((r - 0.1) * cosine(th), y + 0.1, (r - 0.1) * sine(th));

    // Draw outer vertex
    if (textureEnabled) {glTexCoord2f(0, texFact);}
    glVertex3d(r * cosine(th), y + 0.1, r * sine(th));
  }
  glEnd();
}

// drawClockMarkers() protected member function
// Contains logic to draw the hour markers on the clock face
void AnalogClock::drawClockMarkers(double y) {
  for (int th = 0; th <= 360; th += 30) {
    glBegin(GL_QUADS);
    if (lightingEnabled) {glNormal3d(0.0, 1.0, 0.0);}
    if (textureEnabled) {glTexCoord2f(0, 0);}
    glVertex3d((r - 0.5) * cosine(th - 1.5), y + 0.05, (r - 0.5) * sine(th - 1.5)); // bottom right point
    if (textureEnabled) {glTexCoord2f(0, texFact);}
    glVertex3d((r - 0.2) * cosine(th - 1.5), y + 0.05, (r - 0.2) * sine(th - 1.5)); // top right point
    if (textureEnabled) {glTexCoord2f(texFact, 0);}
    glVertex3d((r - 0.2) * cosine(th + 1.5), y + 0.05, (r - 0.2) * sine(th + 1.5)); // top left point
    if (textureEnabled) {glTexCoord2f(texFact, texFact);}
    glVertex3d((r - 0.5) * cosine(th + 1.5), y + 0.05, (r - 0.5) * sine(th + 1.5)); // bottom left point
    glEnd();
  }
}

// drawHourHand() protected member function
// Contains logic to draw the clock's hour hand
void AnalogClock::drawHourHand(double y) {

}

// drawMinuteHand() protected member function
// Contains logic to draw the clock's minute hand
void AnalogClock::drawMinuteHand(double y) {

}

// sine() private member function
// Returns the sine of the provided angle in degrees
double AnalogClock::sine(double angle) { return sin(angle * (3.14159265 / 180)); }

// cosine() private member function
// Returns the cosine of the provided angle in degrees
double AnalogClock::cosine(double angle) { return cos(angle * (3.14159265 / 180)); }
