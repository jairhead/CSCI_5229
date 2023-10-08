/*
 * File: Axes.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the Axes class, a child class
 *              of the BaseObject abstract class.
 */

#include "Axes.h"

// Default Constructor
Axes::Axes() { }

// Destructor
Axes::~Axes() { }

// setAxisColors() public member function
// Sets the axes' color values
void Axes::setAxisColors(double r, double g, double b) {
  axisRed = r;
  axisGreen = g;
  axisBlue = b;
}

// setTextColors() public member function
// Sets the text color values
void Axes::setTextColors(double r, double g, double b) {
  textRed = r;
  textGreen = g;
  textBlue = b;
}

// draw() public member function
// Contains logic to draw the object
void Axes::draw() {
  // Draw gray x, y, z axes
  if (lightingEnabled) {glDisable(GL_LIGHTING);}
  glColor3d(axisRed, axisGreen, axisBlue);
  glLineWidth(thickness);
  glBegin(GL_LINES);
  glVertex3d(0.0, 0.0, 0.0);
  glVertex3d(1.0, 0.0, 0.0);
  glVertex3d(0.0, 0.0, 0.0);
  glVertex3d(0.0, 1.0, 0.0);
  glVertex3d(0.0, 0.0, 0.0);
  glVertex3d(0.0, 0.0, 1.0);
  glEnd();

  // Draw dots at end of axes
  glPointSize(10);
  glEnable(GL_POINT_SMOOTH);
  glBegin(GL_POINTS);
  glVertex4d(0, 0, 0, w);
  glVertex4d(1, 0, 0, w);
  glVertex4d(0, 1, 0, w);
  glVertex4d(0, 0, 1, w);
  glEnd();
  glDisable(GL_POINT_SMOOTH);

  // Label axes in white
  glColor3d(textRed, textGreen, textBlue);
  glRasterPos3d(1.1, 0, 0);
  displayText("x");
  glRasterPos3d(0, 1.1, 0);
  displayText("y");
  glRasterPos3d(0, 0, 1.1);
  displayText("z");

  // End
  if (lightingEnabled) {glEnable(GL_LIGHTING);}
}

// displayText() private member function
// Helper method that displays a string to the scene
void Axes::displayText(std::string text) {
  for (size_t i = 0; i < text.size(); i++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
  }
}
