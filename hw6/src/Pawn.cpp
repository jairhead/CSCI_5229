/*
 * File: Pawn.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the Pawn class, a child class
 *              of the BaseObject abstract class.
 */

#include "Pawn.h"

// Default Constructor
Pawn::Pawn() {
  top = new Sphere();
  scaleArray[0] = 0.3;
  scaleArray[1] = 0.3;
  scaleArray[2] = 0.3;
}

// Destructor
Pawn::~Pawn() { }

// color() public member function
// Sets the object's color values
void Pawn::color(double r, double g, double b) {
  colorArray[0] = r;
  colorArray[1] = g;
  colorArray[2] = b;
  shinyFactor = 1.0;
}

// setTextureFactor() public member function
// Sets the texture factor (scaling) for the pawn
void Pawn::setTextureFactor(float tf) {
  texFact = tf;
  top->setTextureFactor(tf);
}

// setTexture() public overloaded member function
// Sets the texture of the pawn
void Pawn::setTexture(unsigned int *tex) {
  texture = tex;
  top->setTexture(tex);
}

// draw() public member function
// Contains logic to draw the object
void Pawn::draw() {
  // Set lighting properties
  if (lightingEnabled) {
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shinyFactor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularArray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissionArray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseArray);
    top->enableLighting();
  }
  else {
    top->disableLighting();
  }

  // Set texture properties
  if (textureEnabled) {
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, *texture);
    top->enableTexture();
  }
  else {
    top->disableTexture();
  }

  // Save transformation and set up
  glPushMatrix();

  // Translate -> Rotate -> Scale
  glTranslated(posArray[0], posArray[1], posArray[2]);
  glRotated(theta, 0, 1, 0);
  glScaled(scaleArray[0], scaleArray[1], scaleArray[2]);
  glColor3f(colorArray[0], colorArray[1], colorArray[2]);

  // Declare xyz tracking values
  double xVal1 = 1.00; double xVal2 = 1.00;
  double yVal1 = 0.00; double yVal2 = 0.20;
  double zVal1 = 1.00; double zVal2 = 1.00;
  double ph = 0.00;

  // Base bottom (circle)
  drawCap(xVal1, yVal1, -1.0);

  // Base perimeter
  drawCyl(xVal1, xVal2, yVal1, yVal2, zVal1, zVal2, ph);

  // Adjust xyz tracking values
  xVal1 = 1.00; xVal2 = 0.95;
  yVal1 = 0.20; yVal2 = 0.30;
  zVal1 = xVal1; zVal2 = xVal2;
  ph = 26.565;

  // Slanted base section 1
  drawCyl(xVal1, xVal2, yVal1, yVal2, zVal1, zVal2, ph);

  // Adjust xyz tracking values
  xVal1 = 0.95; xVal2 = 0.65;
  yVal1 = 0.30; yVal2 = 0.50;
  zVal1 = xVal1; zVal2 = xVal2;
  ph = 56.31;

  // Slanted base section 2
  drawCyl(xVal1, xVal2, yVal1, yVal2, zVal1, zVal2, ph);

  // Adjust xyz tracking values
  xVal1 = 0.65; xVal2 = 0.55;
  yVal1 = 0.50; yVal2 = 0.70;
  zVal1 = xVal1; zVal2 = xVal2;
  ph = 26.565;

  // Slanted base section 3
  drawCyl(xVal1, xVal2, yVal1, yVal2, zVal1, zVal2, ph);

  // Adjust xyz tracking values
  xVal1 = 0.55; xVal2 = 0.40;
  yVal1 = 0.70; yVal2 = 0.80;
  zVal1 = xVal1; zVal2 = xVal2;
  ph = 5.711;

  // Slanted base section 4
  drawCyl(xVal1, xVal2, yVal1, yVal2, zVal1, zVal2, ph);

  // Adjust xyz tracking values
  xVal1 = 0.40; xVal2 = 0.30;
  yVal1 = 0.80; yVal2 = 1.80;
  zVal1 = xVal1; zVal2 = xVal2;
  ph = 56.31;

  // Tall middle section
  drawCyl(xVal1, xVal2, yVal1, yVal2, zVal1, zVal2, ph);

  // Adjust xyz tracking values
  xVal1 = 0.30; xVal2 = 0.45;
  yVal1 = 1.80; yVal2 = 1.85;
  zVal1 = xVal1; zVal2 = xVal2;
  ph = -71.565;

  // Collar (bottom)
  drawCyl(xVal1, xVal2, yVal1, yVal2, zVal1, zVal2, ph);

  // Adjust xyz tracking values
  xVal1 = 0.45; xVal2 = 0.45;
  yVal1 = 1.85; yVal2 = yVal1;
  zVal1 = xVal1; zVal2 = xVal2;
  ph = 71.565;

  // Collar (top)
  drawCap(xVal1, yVal1, 1.0);

  // Top sphere
  yVal1 = 2.25;
  top->translate(0.0, yVal1, 0.0);
  top->color(colorArray[0], colorArray[1], colorArray[2]);
  top->scale(0.45, 0.45, 0.45);
  top->draw();

  // End
  glPopMatrix();
  if (textureEnabled) {glDisable(GL_TEXTURE_2D);}
}

// drawCap() private member function
// Contains logic to draw a circular cap
void Pawn::drawCap(double r, double y, double yNorm) {
  for (int th = 0; th <= 360; th += d) {
    // Draw normal vector
    glBegin(GL_TRIANGLES);
    if (lightingEnabled) {glNormal3d(0.0, yNorm, 0.0);}

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

// drawCyl() private member function
// Contains logic to draw a cylinder-like portion of the object
void Pawn::drawCyl(double x1, double x2,
                   double y1, double y2,
                   double z1, double z2,
                   double ph) {
  glBegin(GL_QUAD_STRIP);
  for (int th = 0; th <= 360; th += d) {
    // Draw normal vector
    if (lightingEnabled) {glNormal3d(cosine(th), sine(ph), sine(th));}

    // Draw bottom right vertex
    if (textureEnabled) {glTexCoord2f(0, 0);}
    glVertex3d(x1 * cosine(th), y1, z1 * sine(th));

    // Draw top right vertex
    if (textureEnabled) {glTexCoord2f(0, texFact);}
    glVertex3d(x2 * cosine(th), y2, z2 * sine(th));

    // Draw bottom left vertex
    if (textureEnabled) {glTexCoord2f(texFact, 0);}
    glVertex3d(x1 * cosine(th + d), y1, z1 * sine(th + d));

    // Draw top left vertex
    if (textureEnabled) {glTexCoord2f(texFact, texFact);}
    glVertex3d(x2 * cosine(th + d), y2, z2 * sine(th + d));
  }
  glEnd();
}

// sine() private member function
// Returns the sine of the provided angle in degrees
double Pawn::sine(double angle) { return sin(angle * (3.14159265 / 180)); }

// cosine() private member function
// Returns the cosine of the provided angle in degrees
double Pawn::cosine(double angle) { return cos(angle * (3.14159265 / 180)); }
