/*
 * File: Icosahedron.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the Icosahedron class, a child class
 *              of the BaseObject abstract class.
 */

#include "Icosahedron.h"

// Default Constructor
Icosahedron::Icosahedron() { }

// Destructor
Icosahedron::~Icosahedron() { }

// color() public member function
// Sets the object's color values
void Icosahedron::color(double r, double g, double b) {
  colorArray[0] = r;
  colorArray[1] = g;
  colorArray[2] = b;
}

// draw() public member function
// Contains logic to draw the object
void Icosahedron::draw() {
  // Save transformation and set up
  glPushMatrix();

  // Translate -> Rotate -> Scale
  glTranslated(posArray[0], posArray[1], posArray[2]);
  glRotated(theta, 0, 1, 0);
  glScaled(scaleArray[0], scaleArray[1], scaleArray[2]);
  glColor3d(colorArray[0], colorArray[1], colorArray[2]);

  // Draw the object
  /*for (int i = 0; i < numSides; i++) {
    drawTriangle(vertices[index[i]],
                 vertices[index[i]],
                 vertices[index[i]]);
  }*/

  // End
  glEnd();
  glPopMatrix();
}

// drawTriangle() private member function
// Contains logic to draw a triangle
void Icosahedron::drawTriangle(double vertex1[3], double vertex2[3], double vertex3[3]) {
  //  Planar vector 0
  double x0 = vertex1[0] - vertex2[0];
  double y0 = vertex1[1] - vertex2[1];
  double z0 = vertex1[2] - vertex2[2];

  //  Planar vector 1
  double x1 = vertex3[0] - vertex1[0];
  double y1 = vertex3[1] - vertex1[1];
  double z1 = vertex3[2] - vertex1[2];

  //  Normal
  double normalX = (y0 * z1) - (y1 * z0);
  double normalY = (z0 * x1) - (z1 * x0);
  double normalZ = (x0 * y1) - (x1 * y0);

  // Draw triangle
  glNormal3f(normalX, normalY, normalZ);
  glBegin(GL_TRIANGLES);
  glVertex3d(vertex1[0], vertex1[1], vertex1[2]);
  glVertex3f(vertex2[0], vertex2[1], vertex2[2]);
  glVertex3f(vertex3[0], vertex3[1], vertex3[2]);

  // End
  glEnd();
}