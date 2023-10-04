/*
 * File: Cloud.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the Cloud class, a child
 *              class of the BaseObject abstract class.
 */

#include "Cloud.h"

// Constructor
Cloud::Cloud() {
  lobe1 = new Sphere(0.0, 0.0, 0.32, 0.1, 0.0);
  lobe2 = new Sphere(0.06, 0.0, 0.2, 0.11, 0.0);
  lobe3 = new Sphere(0.04, 0.0, 0.1, 0.07, 0.0);
}

// Destructor
Cloud::~Cloud() { }

// translate() public member function
// Sets the cloud's coordinate values
void Cloud::translate(double x, double y, double z) {
  xPos = x;
  yPos = y;
  zPos = z;
}

// color() public member function
// Sets the street lamp's colors
void Cloud::color(bool day) {
  if (day) {
    dayTime = true;
    cloudC[0][0] = cloudC[1][0];
    cloudC[0][1] = cloudC[1][1];
    cloudC[0][2] = cloudC[1][2];
  }
  else {
    dayTime = false;
    cloudC[0][0] = cloudC[2][0];
    cloudC[0][1] = cloudC[2][1];
    cloudC[0][2] = cloudC[2][2];
  }
}

// rotate() public member function
// Sets the angle for drawing the cloud
void Cloud::rotate(double th) {
  theta = th;
}

// draw()
// Contains logic to draw a cloud
void Cloud::draw() {
  // Save transformation, translate and rotate
  glPushMatrix();
  glTranslated(xPos, yPos, zPos);
  glRotated(theta, 0, 1, 0);

  // Draw the first lobe
  lobe1->color(cloudC[0][0], cloudC[0][1], cloudC[0][2]);
  lobe1->draw();

  // Draw the second lobe
  lobe2->color(cloudC[0][0], cloudC[0][1], cloudC[0][2]);
  lobe2->draw();

  // Draw the third lobe
  lobe3->color(cloudC[0][0], cloudC[0][1], cloudC[0][2]);
  lobe3->draw();

  // Undo transformations
  glPopMatrix();
}