/*
 * File: ConiferousTree.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the ConiferousTree class, a child
 *              class of the BaseObject abstract class.
 */

#include "ConiferousTree.h"

// Constructor
ConiferousTree::ConiferousTree() {
  // Get pointer to data structure
  data = WeatherData::getInstance();
}

// Destructor
ConiferousTree::~ConiferousTree() { }

// setTextureFactor() public member function
// Sets the texture factor (scaling) for the pawn
void ConiferousTree::setTextureFactor(float tf) {texFact = tf;}

// setStumpTexture() public overloaded member function
// Sets the texture of the tree's stump
void ConiferousTree::setTrunkTexture(unsigned int *tex) {
  treeTrunkTexture = tex;
  textureEnabled = true;
}

// setLeafTexture() public overloaded member function
// Sets the texture of the tree's leaves
void ConiferousTree::setLeafTexture(unsigned int *tex) {
  leafTexture = tex;
  textureEnabled = true;
}

// setSnowyLeafTexture() public overloaded member function
// Sets the texture of the tree's leaves for snow
void ConiferousTree::setSnowyLeafTexture(unsigned int *tex) {
  snowyLeafTexture = tex;
  textureEnabled = true;
}

// draw() public member function
// Contains logic to draw the object
void ConiferousTree::draw() {
  // Set lighting properties
  if (lightingEnabled) {
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shinyFactor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularArray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissionArray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseArray);
  }

  // Save transformation; Translate -> Rotate -> Scale
  glPushMatrix();
  glTranslated(posArray[0], posArray[1], posArray[2]);
  glRotated(theta, 0, 1, 0);
  glScaled(scaleArray[0], scaleArray[1], scaleArray[2]);
  glColor3f(colorArray[0], colorArray[1], colorArray[2]);

  // Set tree trunk texture
  if (textureEnabled) {
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, *treeTrunkTexture);
  }

  // Draw base segment of trunk
  double r1 = 1.00; double r2 = 0.90;
  double h1 = 0.00; double h2 = 1.0;
  double hyp = Utilities::hypotenuse((r1 - r2), (h2 - h1));
  double ph = Utilities::arcSine((r1-r2)/(hyp));
  drawTrunkSection(r1, r2, h1, h2, r1, r2, ph);

  // Draw first middle segment of trunk
  r1 = r2; r2 = r1 - 0.1;
  h1 = h2; h2 = h1 + 1.0;
  hyp = Utilities::hypotenuse((r1 - r2), (h2 - h1));
  ph = Utilities::arcSine((r1-r2)/(hyp));
  drawTrunkSection(r1, r2, h1, h2, r1, r2, ph);

  // Draw second middle segment of trunk
  r1 = r2; r2 = r1 - 0.1;
  h1 = h2; h2 = h1 + 1.0;
  hyp = Utilities::hypotenuse((r1 - r2), (h2 - h1));
  ph = Utilities::arcSine((r1-r2)/(hyp));
  drawTrunkSection(r1, r2, h1, h2, r1, r2, ph);

  // Draw third middle segment of trunk
  r1 = r2; r2 = r1 - 0.1;
  h1 = h2; h2 = h1 + 1.0;
  hyp = Utilities::hypotenuse((r1 - r2), (h2 - h1));
  ph = Utilities::arcSine((r1-r2)/(hyp));
  drawTrunkSection(r1, r2, h1, h2, r1, r2, ph);

  // Draw fourth middle segment of trunk
  r1 = r2; r2 = r1 - 0.1;
  h1 = h2; h2 = h1 + 1.0;
  hyp = Utilities::hypotenuse((r1 - r2), (h2 - h1));
  ph = Utilities::arcSine((r1-r2)/(hyp));
  drawTrunkSection(r1, r2, h1, h2, r1, r2, ph);

  // Draw fifth middle segment of trunk
  r1 = r2; r2 = r1 - 0.1;
  h1 = h2; h2 = h1 + 1.0;
  hyp = Utilities::hypotenuse((r1 - r2), (h2 - h1));
  ph = Utilities::arcSine((r1-r2)/(hyp));
  drawTrunkSection(r1, r2, h1, h2, r1, r2, ph);

  // Draw sixth middle segment of trunk
  r1 = r2; r2 = r1 - 0.1;
  h1 = h2; h2 = h1 + 1.0;
  hyp = Utilities::hypotenuse((r1 - r2), (h2 - h1));
  ph = Utilities::arcSine((r1-r2)/(hyp));
  drawTrunkSection(r1, r2, h1, h2, r1, r2, ph);

  // Draw seventh middle segment of trunk
  r1 = r2; r2 = r1 - 0.1;
  h1 = h2; h2 = h1 + 1.0;
  hyp = Utilities::hypotenuse((r1 - r2), (h2 - h1));
  ph = Utilities::arcSine((r1-r2)/(hyp));
  drawTrunkSection(r1, r2, h1, h2, r1, r2, ph);

  // Draw eighth middle segment of trunk
  r1 = r2; r2 = r1 - 0.1;
  h1 = h2; h2 = h1 + 1.0;
  hyp = Utilities::hypotenuse((r1 - r2), (h2 - h1));
  ph = Utilities::arcSine((r1-r2)/(hyp));
  drawTrunkSection(r1, r2, h1, h2, r1, r2, ph);

  // Draw ninth middle segment of trunk
  r1 = r2; r2 = r1 - 0.1;
  h1 = h2; h2 = h1 + 1.0;
  hyp = Utilities::hypotenuse((r1 - r2), (h2 - h1));
  ph = Utilities::arcSine((r1-r2)/(hyp));
  drawTrunkSection(r1, r2, h1, h2, r1, r2, ph);

  // Set leaves texture
  char weatherCondition = data->getCurrentWeatherCondition();
  if (textureEnabled && (weatherCondition == 's' || weatherCondition == 'm')) {
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, *snowyLeafTexture);
  }
  else if (textureEnabled) {
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, *leafTexture);
  }

  // Draw first middle leaves
  r1 = 3.50; r2 = 0.90;
  h1 = 1.50; h2 = 2.0;
  hyp = Utilities::hypotenuse((r1 - r2), (h2 - h1));
  ph = Utilities::arcSine((r1-r2)/(hyp));
  drawLeaves(r1, r2, h1, h2, r1, r2, ph);

  // Draw second middle leaves
  r1 = r1 - 0.3; r2 = r2 - 0.1;
  h1 = h2 + 0.5; h2 = h1 + 0.5;
  hyp = Utilities::hypotenuse((r1 - r2), (h2 - h1));
  ph = Utilities::arcSine((r1-r2)/(hyp));
  drawLeaves(r1, r2, h1, h2, r1, r2, ph);

  // Draw third middle leaves
  r1 = r1 - 0.3; r2 = r2 - 0.1;
  h1 = h2 + 0.5; h2 = h1 + 0.5;
  hyp = Utilities::hypotenuse((r1 - r2), (h2 - h1));
  ph = Utilities::arcSine((r1-r2)/(hyp));
  drawLeaves(r1, r2, h1, h2, r1, r2, ph);

  // Draw fourth middle leaves
  r1 = r1 - 0.3; r2 = r2 - 0.1;
  h1 = h2 + 0.5; h2 = h1 + 0.5;
  hyp = Utilities::hypotenuse((r1 - r2), (h2 - h1));
  ph = Utilities::arcSine((r1-r2)/(hyp));
  drawLeaves(r1, r2, h1, h2, r1, r2, ph);

  // Draw fifth middle leaves
  r1 = r1 - 0.3; r2 = r2 - 0.1;
  h1 = h2 + 0.5; h2 = h1 + 0.5;
  hyp = Utilities::hypotenuse((r1 - r2), (h2 - h1));
  ph = Utilities::arcSine((r1-r2)/(hyp));
  drawLeaves(r1, r2, h1, h2, r1, r2, ph);

  // Draw sixth middle leaves
  r1 = r1 - 0.3; r2 = r2 - 0.1;
  h1 = h2 + 0.5; h2 = h1 + 0.5;
  hyp = Utilities::hypotenuse((r1 - r2), (h2 - h1));
  ph = Utilities::arcSine((r1-r2)/(hyp));
  drawLeaves(r1, r2, h1, h2, r1, r2, ph);

  // Draw seventh middle leaves
  r1 = r1 - 0.3; r2 = r2 - 0.1;
  h1 = h2 + 0.5; h2 = h1 + 0.5;
  hyp = Utilities::hypotenuse((r1 - r2), (h2 - h1));
  ph = Utilities::arcSine((r1-r2)/(hyp));
  drawLeaves(r1, r2, h1, h2, r1, r2, ph);

  // Draw eighth middle leaves
  r1 = r1 - 0.3; r2 = r2 - 0.1;
  h1 = h2 + 0.5; h2 = h1 + 0.5;
  hyp = Utilities::hypotenuse((r1 - r2), (h2 - h1));
  ph = Utilities::arcSine((r1-r2)/(hyp));
  drawLeaves(r1, r2, h1, h2, r1, r2, ph);

  // Draw top leaves
  r1 = r1 - 0.3; r2 = 0.0;
  h1 = h2 + 0.5; h2 = h1 + 0.5;
  hyp = Utilities::hypotenuse((r1 - r2), (h2 - h1));
  ph = Utilities::arcSine((r1-r2)/(hyp));
  drawLeaves(r1, r2, h1, h2, r1, r2, ph);

  // End
  glPopMatrix();
  if (textureEnabled) {glDisable(GL_TEXTURE_2D);}
}

// drawTrunkSection() private member function
// Contains logic to draw a portion of the tree trunk
void ConiferousTree::drawTrunkSection(double x1, double x2,
                                      double y1, double y2,
                                      double z1, double z2,
                                      double ph) {
  glBegin(GL_QUAD_STRIP);
  for (int th = 0; th <= 360; th += d) {
    // Draw normal vector
    if (lightingEnabled) {
      glNormal3d(Utilities::cosine(th), Utilities::sine(ph), Utilities::sine(th));
    }

    // Draw bottom right vertex
    float texP1 = (th) / 360.0; float texP2 = (th + d) / 360.0;
    if (textureEnabled) {glTexCoord2f(texP1, texP1);}
    glVertex3d(x1 * Utilities::cosine(th), y1, z1 * Utilities::sine(th));

    // Draw top right vertex
    if (textureEnabled) {glTexCoord2f(texP1, 1.0);}
    glVertex3d(x2 * Utilities::cosine(th), y2, z2 * Utilities::sine(th));

    // Draw bottom left vertex
    if (textureEnabled) {glTexCoord2f(texP2, 0.0);}
    glVertex3d(x1 * Utilities::cosine(th + d), y1, z1 * Utilities::sine(th + d));

    // Draw top left vertex
    if (textureEnabled) {glTexCoord2f(texP2, 1.0);}
    glVertex3d(x2 * Utilities::cosine(th + d), y2, z2 * Utilities::sine(th + d));
  }
  glEnd();
}

// drawLeaves() private member function
// Contains logic to draw a circumference of leaves on the tree
void ConiferousTree::drawLeaves(double x1, double x2,
                                double y1, double y2,
                                double z1, double z2,
                                double ph) {
  for (int th = 0; th <= 360; th += d) {
    // Draw top of leaf section
    glBegin(GL_QUADS);
    if (lightingEnabled) {glNormal3d(Utilities::cosine(th), Utilities::sine(ph), Utilities::sine(th));}
    if (textureEnabled) {glTexCoord2f(0.0, 0.0);}
    glVertex3d(x1 * Utilities::cosine(th), y1, z1 * Utilities::sine(th)); // bottom right
    if (textureEnabled) {glTexCoord2f(0.0, 0.5);}
    glVertex3d(x2 * Utilities::cosine(th), y2, z2 * Utilities::sine(th)); // top right
    if (textureEnabled) {glTexCoord2f(0.5, 0.0);}
    glVertex3d(x2 * Utilities::cosine(th + d), y2, z2 * Utilities::sine(th + d)); // top left
    if (textureEnabled) {glTexCoord2f(0.5, 0.5);}
    glVertex3d(x1 * Utilities::cosine(th + d/10), y1, z1 * Utilities::sine(th + d/10)); // bottom left
    glEnd();

    // Draw right side of leaf section
    glBegin(GL_TRIANGLES);
    if (lightingEnabled) {glNormal3d(Utilities::cosine(th - 90.0), 0.0, Utilities::sine(th - 90.0));}
    if (textureEnabled) {glTexCoord2f(0, 0);}
    glVertex3d(x1 * Utilities::cosine(th), y1, z1 * Utilities::sine(th)); // bottom outer
    if (textureEnabled) {glTexCoord2f(0.0, 0.5);}
    glVertex3d(x2 * Utilities::cosine(th), y2, z2 * Utilities::sine(th)); // top point
    if (textureEnabled) {glTexCoord2f(0.5, 0.0);}
    glVertex3d(x2 * Utilities::cosine(th), y1, z2 * Utilities::sine(th)); // bottom inner
    glEnd();

    // Draw right side of leaf section
    glBegin(GL_TRIANGLES);
    if (lightingEnabled) {glNormal3d(Utilities::cosine(th + 90.0), 0.0, Utilities::sine(th + 90.0));}
    if (textureEnabled) {glTexCoord2f(0, 0);}
    glVertex3d(x1 * Utilities::cosine(th + d/10), y1, z1 * Utilities::sine(th + d/10)); // bottom outer
    if (textureEnabled) {glTexCoord2f(0.0, 1.0);}
    glVertex3d(x2 * Utilities::cosine(th + d), y2, z2 * Utilities::sine(th + d)); // top point
    if (textureEnabled) {glTexCoord2f(1.0, 0.0);}
    glVertex3d(x2 * Utilities::cosine(th + d), y1, z2 * Utilities::sine(th + d)); // bottom inner
    glEnd();

    // Draw bottom of leaf section
    glBegin(GL_QUADS);
    if (lightingEnabled) {glNormal3d(0.0, -1.0, 0.0);}
    if (textureEnabled) {glTexCoord2f(0.0, 0.0);}
    glVertex3d(x1 * Utilities::cosine(th), y1, z1 * Utilities::sine(th)); // outer right
    if (textureEnabled) {glTexCoord2f(0.0, 0.5);}
    glVertex3d(x2 * Utilities::cosine(th), y1, z2 * Utilities::sine(th)); // inner right
    if (textureEnabled) {glTexCoord2f(0.5, 0.0);}
    glVertex3d(x2 * Utilities::cosine(th + d), y1, z2 * Utilities::sine(th + d)); // inner left
    if (textureEnabled) {glTexCoord2f(0.5, 0.5);}
    glVertex3d(x1 * Utilities::cosine(th + d/10), y1, z1 * Utilities::sine(th + d/10)); // outer left
    glEnd();
  }
}