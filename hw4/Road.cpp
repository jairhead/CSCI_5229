/*
 * File: Road.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the Road class, a child
 *              class of the BaseObject abstract class.
 */

#include "Road.h"

// Constructor
Road::Road() {
  asphalt = new RectangularPrism();
  leftStripe = new RectangularPrism();
  rightStripe = new RectangularPrism();
  centerLeftStripe = new RectangularPrism();
  centerRightStripe = new RectangularPrism();
}

// Destructor
Road::~Road() { }

// scale() public member function
// Sets the road's scaling values
void Road::scale(double s) {
  scalingFactor = s;
}

// translate() public member function
// Sets the road's coordinate values
void Road::translate(double x, double y, double z) {
  xPos = x;
  yPos = y;
  zPos = z;
}

void Road::color(bool day) {
  if (day) {
    asphaltC[0][0] = asphaltC[1][0];
    asphaltC[0][1] = asphaltC[1][1];
    asphaltC[0][2] = asphaltC[1][2];
    whiteStripeC[0][0] = whiteStripeC[1][0];
    whiteStripeC[0][1] = whiteStripeC[1][1];
    whiteStripeC[0][2] = whiteStripeC[1][2];
    orangeStripeC[0][0] = orangeStripeC[1][0];
    orangeStripeC[0][1] = orangeStripeC[1][1];
    orangeStripeC[0][2] = orangeStripeC[1][2];
  }
  else {
    asphaltC[0][0] = asphaltC[2][0];
    asphaltC[0][1] = asphaltC[2][1];
    asphaltC[0][2] = asphaltC[2][2];
    whiteStripeC[0][0] = whiteStripeC[2][0];
    whiteStripeC[0][1] = whiteStripeC[2][1];
    whiteStripeC[0][2] = whiteStripeC[2][2];
    orangeStripeC[0][0] = orangeStripeC[2][0];
    orangeStripeC[0][1] = orangeStripeC[2][1];
    orangeStripeC[0][2] = orangeStripeC[2][2];
  }
}

// rotate() public member function
// Sets the angle for drawing the road
void Road::rotate(double th) {
  theta = th;
}

// draw()
// Contains logic to draw a two-lane road
void Road::draw() {
  // Save transformation, translate and rotate
  glPushMatrix();
  glTranslated(xPos, yPos, zPos);
  glRotated(theta, 1, 0, 0);
  
  // Draw the asphalt
  asphalt->color(asphaltC[0][0], asphaltC[0][1], asphaltC[0][2]);
  asphalt->scale(0.25, 0.02, 1.0);
  asphalt->draw();

  // Draw the left white stripe
  leftStripe->color(whiteStripeC[0][0], whiteStripeC[0][1], whiteStripeC[0][2]);
  leftStripe->scale(0.01, 0.03, 1.0);
  leftStripe->translate(-0.2, 0.0, 0.0);
  leftStripe->draw();

  // Draw the right white stripe
  rightStripe->color(whiteStripeC[0][0], whiteStripeC[0][1], whiteStripeC[0][2]);
  rightStripe->scale(0.01, 0.03, 1.0);
  rightStripe->translate(0.2, 0.0, 0.0);
  rightStripe->draw();

  // Draw the center left stripe
  centerLeftStripe->color(orangeStripeC[0][0], orangeStripeC[0][1], orangeStripeC[0][2]);
  centerLeftStripe->scale(0.01, 0.03, 1.0);
  centerLeftStripe->translate(-0.03, 0.0, 0.0);
  centerLeftStripe->draw();

  // Draw the center right stripe
  centerRightStripe->color(orangeStripeC[0][0], orangeStripeC[0][1], orangeStripeC[0][2]);
  centerRightStripe->scale(0.01, 0.03, 1.0);
  centerRightStripe->translate(0.03, 0.0, 0.0);
  centerRightStripe->draw();
  
  // Undo transformations
  glPopMatrix();
}
