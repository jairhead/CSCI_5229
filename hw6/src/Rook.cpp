/*
 * File: Pawn.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the Rook class, a child class
 *              of the BaseObject abstract class.
 */

#include "Rook.h"

// Default Constructor
Rook::Rook() {
  scaleArray[0] = 0.35;
  scaleArray[1] = 0.35;
  scaleArray[2] = 0.35;
}

// Destructor
Rook::~Rook() { }

// color() public member function
// Sets the object's color values
void Rook::color(double r, double g, double b) {
  colorArray[0] = r;
  colorArray[1] = g;
  colorArray[2] = b;
  shinyFactor = 1.0;
}

// setTextureFactor() public member function
// Sets the texture factor (scaling) for the pawn
void Rook::setTextureFactor(float tf) {texFact = tf;}

// setTexture() public overloaded member function
// Sets the texture of the pawn
void Rook::setTexture(unsigned int *tex) {texture = tex;}

// draw() public member function
// Contains logic to draw the object
void Rook::draw() {
  // Set lighting properties
  if (lightingEnabled) {
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shinyFactor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularArray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissionArray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseArray);
  }

  // Set texture properties
  if (textureEnabled) {
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, *texture);
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
  yVal1 = 0.50; yVal2 = 1.80;
  zVal1 = xVal1; zVal2 = xVal2;
  ph = 4.399;

  // Tall middle section
  drawCyl(xVal1, xVal2, yVal1, yVal2, zVal1, zVal2, ph);

  // Adjust xyz tracking values
  xVal1 = 0.55; xVal2 = 0.75;
  yVal1 = 1.80; yVal2 = 1.95;
  zVal1 = xVal1; zVal2 = xVal2;
  ph = -53.13;

  // Top section (bottom)
  drawCyl(xVal1, xVal2, yVal1, yVal2, zVal1, zVal2, ph);

  // Adjust xyz tracking values
  xVal1 = 0.75; xVal2 = 0.75;
  yVal1 = 1.95; yVal2 = 2.55;
  zVal1 = xVal1; zVal2 = xVal2;
  ph = 0.0;

  // Top section (middle)
  drawCyl(xVal1, xVal2, yVal1, yVal2, zVal1, zVal2, ph);

  // Adjust xyz tracking values
  xVal1 = 0.75; xVal2 = 0.75;
  yVal1 = 2.55; yVal2 = yVal1;
  zVal1 = xVal1; zVal2 = xVal2;
  ph = 0.0;

  // Collar (top)
  drawCap(xVal1, yVal1, 1.0);

  // Adjust xyz tracking values
  xVal1 = 0.75; xVal2 = 0.55;
  yVal1 = 2.55; yVal2 = 2.75;
  zVal1 = xVal1; zVal2 = xVal2;
  ph = 0.0;

  // Top section (battlements)
  for (int th = 0; th <= 360; th += 2*d) {
    // Outside of battlement
    glBegin(GL_QUADS);
    if (lightingEnabled) {glNormal3d(cosine(th), 0.0, sine(th));}
    if (textureEnabled) {glTexCoord2f(0, 0);}
    glVertex3d(xVal1 * cosine(th), yVal1, zVal1 * sine(th)); // bottom right point
    if (textureEnabled) {glTexCoord2f(0, texFact);}
    glVertex3d(xVal1 * cosine(th), yVal2, zVal1 * sine(th)); // top right point
    if (textureEnabled) {glTexCoord2f(texFact, 0);}
    glVertex3d(xVal1 * cosine(th + d), yVal2, zVal1 * sine(th + d)); // top point
    if (textureEnabled) {glTexCoord2f(texFact, texFact);}
    glVertex3d(xVal1 * cosine(th + d), yVal1, zVal1 * sine(th + d)); // bottom point
    glEnd();

    // Inside of battlement
    glBegin(GL_QUADS);
    if (lightingEnabled) {glNormal3d(cosine(th + 180.0), 0.0, sine(th + 180.0));}
    if (textureEnabled) {glTexCoord2f(0, 0);}
    glVertex3d(xVal2 * cosine(th), yVal1, zVal2 * sine(th)); // bottom point
    if (textureEnabled) {glTexCoord2f(0, texFact);}
    glVertex3d(xVal2 * cosine(th), yVal2, zVal2 * sine(th)); // top point
    if (textureEnabled) {glTexCoord2f(texFact, 0);}
    glVertex3d(xVal2 * cosine(th + d), yVal2, zVal2 * sine(th + d)); // top point
    if (textureEnabled) {glTexCoord2f(texFact, texFact);}
    glVertex3d(xVal2 * cosine(th + d), yVal1, zVal2 * sine(th + d)); // bottom point
    glEnd();

    // Left side of battlement
    glBegin(GL_QUADS);
    if (lightingEnabled) {glNormal3d(cosine(th - 90.0), 0.0, sine(th - 90.0));}
    if (textureEnabled) {glTexCoord2f(0, 0);}
    glVertex3d(xVal1 * cosine(th), yVal1, zVal1 * sine(th)); // bottom point
    if (textureEnabled) {glTexCoord2f(0, texFact);}
    glVertex3d(xVal1 * cosine(th), yVal2, zVal1 * sine(th)); // top point
    if (textureEnabled) {glTexCoord2f(texFact, 0);}
    glVertex3d(xVal2 * cosine(th), yVal2, zVal2 * sine(th)); // top point
    if (textureEnabled) {glTexCoord2f(texFact, texFact);}
    glVertex3d(xVal2 * cosine(th), yVal1, zVal2 * sine(th)); // bottom point
    glEnd();

    // Right side of battlement
    glBegin(GL_QUADS);
    if (lightingEnabled) {glNormal3d(cosine(th + 90.0), 0.0, sine(th + 90.0));}
    if (textureEnabled) {glTexCoord2f(0, 0);}
    glVertex3d(xVal1 * cosine(th + d), yVal1, zVal1 * sine(th + d)); // bottom point
    if (textureEnabled) {glTexCoord2f(0, texFact);}
    glVertex3d(xVal1 * cosine(th + d), yVal2, zVal1 * sine(th + d)); // top point
    if (textureEnabled) {glTexCoord2f(texFact, 0);}
    glVertex3d(xVal2 * cosine(th + d), yVal2, zVal2 * sine(th + d)); // top point
    if (textureEnabled) {glTexCoord2f(texFact, texFact);}
    glVertex3d(xVal2 * cosine(th + d), yVal1, zVal2 * sine(th + d)); // bottom point
    glEnd();

    // Top of battlement
    glBegin(GL_QUADS);
    if (lightingEnabled) {glNormal3d(0.0, 1.0, 0.0);}
    if (textureEnabled) {glTexCoord2f(0, 0);}
    glVertex3d(xVal1 * cosine(th), yVal2, zVal1 * sine(th)); // left outer
    if (textureEnabled) {glTexCoord2f(0, texFact);}
    glVertex3d(xVal2 * cosine(th), yVal2, zVal2 * sine(th)); // left inner
    if (textureEnabled) {glTexCoord2f(texFact, 0);}
    glVertex3d(xVal2 * cosine(th + d), yVal2, zVal2 * sine(th + d)); // right inner
    if (textureEnabled) {glTexCoord2f(texFact, texFact);}
    glVertex3d(xVal1 * cosine(th + d), yVal2, zVal1 * sine(th + d)); // right outer
    glEnd();
  }

  // End
  glPopMatrix();
  if (textureEnabled) {glDisable(GL_TEXTURE_2D);}
}

// drawCap() private member function
// Contains logic to draw a circular cap
void Rook::drawCap(double r, double y, double yNorm) {
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
void Rook::drawCyl(double x1, double x2,
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
double Rook::sine(double angle) { return sin(angle * (3.14159265 / 180)); }

// cosine() private member function
// Returns the cosine of the provided angle in degrees
double Rook::cosine(double angle) { return cos(angle * (3.14159265 / 180)); }
