/*
 * File: ConiferousTree.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the ConiferousTree class, a child
 *              class of the BaseObject abstract class.
 */

#include "ConiferousTree.h"

// Constructor
ConiferousTree::ConiferousTree() {
  lightingEnabled = true;
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

// draw() public member function
// Contains logic to draw the object
void ConiferousTree::draw() {
  /*std::cout << "ConiferousTree::draw(): testing out the normal vector computations!" << std::endl;
  double point1[] = {0.0, 0.0, 0.0};
  double point2[] = {1.0, 1.0, 0.0};
  double point3[] = {1.0, 1.0, 1.0};
  double vec1[] = {point2[0] - point1[0], point2[1] - point1[1], point2[2] - point1[2]};
  double vec2[] = {point3[0] - point2[0], point3[1] - point2[1], point3[2] - point2[2]};
  double n[] = {0.0, 0.0, 0.0};
  Utilities::computeNormal(vec1, vec2, n);*/
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
  drawCyl(r1, r2, h1, h2, r1, r2, ph);

  // Draw first middle segment of trunk
  r1 = r2; r2 = r1 - 0.1;
  h1 = h2; h2 = h1 + 1.0;
  hyp = Utilities::hypotenuse((r1 - r2), (h2 - h1));
  ph = Utilities::arcSine((r1-r2)/(hyp));
  drawCyl(r1, r2, h1, h2, r1, r2, ph);

  // Draw second middle segment of trunk
  r1 = r2; r2 = r1 - 0.1;
  h1 = h2; h2 = h1 + 1.0;
  hyp = Utilities::hypotenuse((r1 - r2), (h2 - h1));
  ph = Utilities::arcSine((r1-r2)/(hyp));
  drawCyl(r1, r2, h1, h2, r1, r2, ph);

  // Draw third middle segment of trunk
  r1 = r2; r2 = r1 - 0.1;
  h1 = h2; h2 = h1 + 1.0;
  hyp = Utilities::hypotenuse((r1 - r2), (h2 - h1));
  ph = Utilities::arcSine((r1-r2)/(hyp));
  drawCyl(r1, r2, h1, h2, r1, r2, ph);

  // Draw fourth middle segment of trunk
  r1 = r2; r2 = r1 - 0.1;
  h1 = h2; h2 = h1 + 1.0;
  hyp = Utilities::hypotenuse((r1 - r2), (h2 - h1));
  ph = Utilities::arcSine((r1-r2)/(hyp));
  drawCyl(r1, r2, h1, h2, r1, r2, ph);

  // Draw fifth middle segment of trunk
  r1 = r2; r2 = r1 - 0.1;
  h1 = h2; h2 = h1 + 1.0;
  hyp = Utilities::hypotenuse((r1 - r2), (h2 - h1));
  ph = Utilities::arcSine((r1-r2)/(hyp));
  drawCyl(r1, r2, h1, h2, r1, r2, ph);

  // Draw sixth middle segment of trunk
  r1 = r2; r2 = r1 - 0.1;
  h1 = h2; h2 = h1 + 1.0;
  hyp = Utilities::hypotenuse((r1 - r2), (h2 - h1));
  ph = Utilities::arcSine((r1-r2)/(hyp));
  drawCyl(r1, r2, h1, h2, r1, r2, ph);

  // Draw seventh middle segment of trunk
  r1 = r2; r2 = r1 - 0.1;
  h1 = h2; h2 = h1 + 1.0;
  hyp = Utilities::hypotenuse((r1 - r2), (h2 - h1));
  ph = Utilities::arcSine((r1-r2)/(hyp));
  drawCyl(r1, r2, h1, h2, r1, r2, ph);

  // Draw eighth middle segment of trunk
  r1 = r2; r2 = r1 - 0.1;
  h1 = h2; h2 = h1 + 1.0;
  hyp = Utilities::hypotenuse((r1 - r2), (h2 - h1));
  ph = Utilities::arcSine((r1-r2)/(hyp));
  drawCyl(r1, r2, h1, h2, r1, r2, ph);

  // Draw ninth middle segment of trunk
  r1 = r2; r2 = r1 - 0.1;
  h1 = h2; h2 = h1 + 1.0;
  hyp = Utilities::hypotenuse((r1 - r2), (h2 - h1));
  ph = Utilities::arcSine((r1-r2)/(hyp));
  drawCyl(r1, r2, h1, h2, r1, r2, ph);

  // Draw base leaves
  

  // End
  glPopMatrix();
  if (textureEnabled) {glDisable(GL_TEXTURE_2D);}
}

// drawCyl() private member function
// Contains logic to draw a cylinder-like portion of the object
void ConiferousTree::drawCyl(double x1, double x2,
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