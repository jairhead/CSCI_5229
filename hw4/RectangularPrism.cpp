/*
 * File: RectangularPrism.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the Rectangular Prism class,
 *              a child class of the BaseObject abstract class.
 */

#include "RectangularPrism.h"

// Constructor
RectangularPrism::RectangularPrism() { }

// Destructor
RectangularPrism::~RectangularPrism() { }

// scale() member function
// Sets the rectangular prism's scaling values
void RectangularPrism::scale(double dx, double dy, double dz) {
  xScaling = dx;
  yScaling = dy;
  zScaling = dz;
}

// translate() member function
// Sets the rectangular prism's coordinate values
void RectangularPrism::translate(double x, double y, double z) {
  xPos = x;
  yPos = y;
  zPos = z;
}

// color() member function
// Sets the rectangular prism's color values
void RectangularPrism::color(double r, double g, double b) {
  red = r;
  green = g;
  blue = b;
}

// draw() member function
// Contains logic to draw the rectangular prism
void RectangularPrism::draw() {
  // Save transformation, set color, translate and rotate
  glPushMatrix();
  glColor3d(red, green, blue);
  glTranslated(xPos, yPos, zPos);
  glRotated(theta, 0, 1, 0);

  // Front face
  glBegin(GL_QUADS);
  glVertex3f(-xScaling, -yScaling, +zScaling);
  glVertex3f(+xScaling, -yScaling, +zScaling);
  glVertex3f(+xScaling, +yScaling, +zScaling);
  glVertex3f(-xScaling, +yScaling, +zScaling);

  // Back face
  glVertex3f(+xScaling, -yScaling, -zScaling);
  glVertex3f(-xScaling, -yScaling, -zScaling);
  glVertex3f(-xScaling, +yScaling, -zScaling);
  glVertex3f(+xScaling, +yScaling, -zScaling);

  // Right face
  glVertex3f(+xScaling, -yScaling, +zScaling);
  glVertex3f(+xScaling, -yScaling, -zScaling);
  glVertex3f(+xScaling, +yScaling, -zScaling);
  glVertex3f(+xScaling, +yScaling, +zScaling);

  // Left face
  glVertex3f(-xScaling, -yScaling, -zScaling);
  glVertex3f(-xScaling, -yScaling, +zScaling);
  glVertex3f(-xScaling, +yScaling, +zScaling);
  glVertex3f(-xScaling, +yScaling, -zScaling);

  // Top face
  glVertex3f(-xScaling, +yScaling, +zScaling);
  glVertex3f(+xScaling, +yScaling, +zScaling);
  glVertex3f(+xScaling, +yScaling, -zScaling);
  glVertex3f(-xScaling, +yScaling, -zScaling);

  // Bottom face
  glVertex3f(-xScaling, -yScaling, -zScaling);
  glVertex3f(+xScaling, -yScaling, -zScaling);
  glVertex3f(+xScaling, -yScaling, +zScaling);
  glVertex3f(-xScaling, -yScaling, +zScaling);

  // End and pop transformation
  glEnd();
  glPopMatrix();
}
