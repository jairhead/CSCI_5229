/*
 * File: MountainBackdrop.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the Mountain Backdrop class, a child
 *              class of the BaseObject abstract class.
 */

 #include "MountainBackdrop.h"

// Constructor
MountainBackdrop::MountainBackdrop() { }

// Destructor
MountainBackdrop::~MountainBackdrop() { }

// scale() public member function
// Sets the mountainss scaling values
void MountainBackdrop::scale(double dx, double dy, double dz) {
  xScaling = dx;
  yScaling = dy;
  zScaling = dz;
}

// translate() public member function
// Sets the mountain's coordinate values
void MountainBackdrop::translate(double x, double y, double z) {
  xPos = x;
  yPos = y;
  zPos = z;
}

// color() public member function
// Sets the mountain's color values
void MountainBackdrop::color(double r, double g, double b) {
  red = r;
  green = g;
  blue = b;
}

// rotate() public member function
// Sets the initial angle for drawing the mountains
void MountainBackdrop::rotate(double th) {
  theta = th;
}

// draw() public member function
// Contains logic to draw the mountains
void MountainBackdrop::draw() {
  // Save transformation, set color, translate and rotate
  glPushMatrix();
  glColor3d(red, green, blue);
  glTranslated(xPos, yPos, zPos);
  glRotated(90.0, 1, 0, 0);

  // Draw the first mountain
  glBegin(GL_TRIANGLES);
  glVertex3d(-1.0, 0.0, 0.0);
  glVertex3d(-0.3, 0.0, -0.45);
  glVertex3d(-0.1, 0.0, 0.0);
  glEnd();

  // Draw the second mountain
  glBegin(GL_TRIANGLES);
  glVertex3d(-0.6, 0.0, 0.0);
  glVertex3d(0.0, 0.0, -0.52);
  glVertex3d(0.7, 0.0, 0.0);
  glEnd();

  // Draw the third mountain
  glBegin(GL_TRIANGLES);
  glVertex3d(0.1, 0.0, 0.0);
  glVertex3d(0.4, 0.0, -0.40);
  glVertex3d(1.0, 0.0, 0.0);
  glEnd();

  // Undo transformations
  glPopMatrix();
}