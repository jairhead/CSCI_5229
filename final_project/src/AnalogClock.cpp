/*
 * File: AnalogClock.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the AnalogClock class, a child
 *              class of the BaseObject abstract class.
 */

#include "AnalogClock.h"

// Constructor
AnalogClock::AnalogClock() {
  data = WeatherData::getInstance();
}

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
    glBegin(GL_TRIANGLES);
    if (lightingEnabled) {glNormal3d(0.0, y, 0.0);}
    glVertex3d(0.0, y, 0.0);
    glVertex3d(r * Utilities::cosine(th), y, r * Utilities::sine(th));
    glVertex3d(r * Utilities::cosine(th + d), y, r * Utilities::sine(th + d));
    glEnd();
  }
}

// drawClockRim() protected member function
// Contains logic to draw the clock rim
void AnalogClock::drawClockRim(double y) {
  // Outside of clock rim
  glBegin(GL_QUAD_STRIP);
  glColor3f(0.0, 0.0, 0.0);
  for (int th = 0; th <= 360; th += d) {
    if (lightingEnabled) {glNormal3d(Utilities::cosine(th), 0.0, Utilities::sine(th));}
    glVertex3d(r * Utilities::cosine(th), y - 0.05, r * Utilities::sine(th));
    glVertex3d(r * Utilities::cosine(th), y + 0.05, r * Utilities::sine(th));
  }
  glEnd();

  // Inside of clock rim
  glBegin(GL_QUAD_STRIP);
  for (int th = 0; th <= 360; th += d) {
    if (lightingEnabled) {glNormal3d(Utilities::cosine(th + 180.0), 0.0, Utilities::sine(th + 180.0));}
    glVertex3d((r - 0.1) * Utilities::cosine(th), y - 0.05, (r - 0.1) * Utilities::sine(th));
    glVertex3d((r - 0.1) * Utilities::cosine(th), y + 0.05, (r - 0.1) * Utilities::sine(th));
  }
  glEnd();

  // Top of clock rim
  glBegin(GL_QUAD_STRIP);
  for (int th = 0; th <= 360; th += d) {
    if (lightingEnabled) {glNormal3d(0.0, 1.0, 0.0);}
    glVertex3d((r - 0.1) * Utilities::cosine(th), y + 0.05, (r - 0.1) * Utilities::sine(th));
    glVertex3d(r * Utilities::cosine(th), y + 0.05, r * Utilities::sine(th));
  }
  glEnd();

}

// drawClockMarkers() protected member function
// Contains logic to draw the hour markers on the clock face
void AnalogClock::drawClockMarkers(double y) {
  glColor3f(0.0, 0.0, 0.0);
  for (int th = 0; th <= 360; th += 30) {
    glBegin(GL_QUADS);
    if (lightingEnabled) {glNormal3d(0.0, 1.0, 0.0);}
    glVertex3d((r - 0.5) * Utilities::cosine(th - 1.5), y + 0.01, (r - 0.5) * Utilities::sine(th - 1.5)); // bottom right point
    glVertex3d((r - 0.2) * Utilities::cosine(th - 1.5), y + 0.01, (r - 0.2) * Utilities::sine(th - 1.5)); // top right point
    glVertex3d((r - 0.2) * Utilities::cosine(th + 1.5), y + 0.01, (r - 0.2) * Utilities::sine(th + 1.5)); // top left point
    glVertex3d((r - 0.5) * Utilities::cosine(th + 1.5), y + 0.01, (r - 0.5) * Utilities::sine(th + 1.5)); // bottom left point
    glEnd();
  }
}

// drawHourHand() protected member function
// Contains logic to draw the clock's hour hand
void AnalogClock::drawHourHand(double y) {
  // Get the current hour
  int hour = data->getHour();
  int minute = data->getMinute();
  double th = (minute * 0.5);
  if (hour != 12) {th += (hour * 30.0);}

  // Draw an hour hand
  glColor3f(0.73, 0.71, 0.0);
  glBegin(GL_TRIANGLES);
  if (lightingEnabled) {glNormal3d(0.0, 1.0, 0.0);}
  glVertex3d((r - 0.45) * Utilities::cosine(th), y + 0.04, (r - 0.45) * Utilities::sine(th)); // Outermost vertex
  glVertex3d((0.03) * Utilities::cosine(th - 90.0), y + 0.04, (0.03) * Utilities::sine(th - 90.0)); // Left inner vertex
  glVertex3d((0.03) * Utilities::cosine(th + 90.0), y + 0.04, (0.03) * Utilities::sine(th + 90.0)); // Right inner vertex
  glEnd();
}

// drawMinuteHand() protected member function
// Contains logic to draw the clock's minute hand
void AnalogClock::drawMinuteHand(double y) {
  // Get the current minute
  int minute = data->getMinute();
  double th = minute * 6.0;
  
  // Draw a minute hand
  glColor3f(0.73, 0.0, 0.0);
  glBegin(GL_TRIANGLES);
  if (lightingEnabled) {glNormal3d(0.0, 1.0, 0.0);}
  glVertex3d((r - 0.15) * Utilities::cosine(th), y + 0.05, (r - 0.25) * Utilities::sine(th)); // Outermost vertex
  glVertex3d((0.03) * Utilities::cosine(th - 90.0), y + 0.05, (0.03) * Utilities::sine(th - 90.0)); // Left inner vertex
  glVertex3d((0.03) * Utilities::cosine(th + 90.0), y + 0.05, (0.03) * Utilities::sine(th + 90.0)); // Right inner vertex
  glEnd();
}
