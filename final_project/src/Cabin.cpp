/*
 * File: Cabin.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the Cabin class, a child
 *              class of the BaseObject abstract class.
 */

#include "Cabin.h"

// Constructor
Cabin::Cabin() {
  // Get pointer to data structure
  data = WeatherData::getInstance();

  // Initialize front fascia logs
  fLog1 = new Log(); fLog1->setPhi(90.0);
  fLog2 = new Log(); fLog2->setPhi(90.0);
  fLog3 = new Log(); fLog3->setPhi(90.0);
  fLog4 = new Log(); fLog4->setPhi(90.0);
  fLog5 = new Log(); fLog5->setPhi(90.0);
  fLog6 = new Log(); fLog6->setPhi(90.0);
  fLog7 = new Log(); fLog7->setPhi(90.0);
  fLog8 = new Log(); fLog8->setPhi(90.0);
  fLog9 = new Log(); fLog9->setPhi(90.0);

  // Initialize left side logs
  lLog1 = new Log(); lLog1->setPhi(90.0); lLog1->setTheta(90.0);
  lLog2 = new Log(); lLog2->setPhi(90.0); lLog2->setTheta(90.0);
  lLog3 = new Log(); lLog3->setPhi(90.0); lLog3->setTheta(90.0);
  lLog4 = new Log(); lLog4->setPhi(90.0); lLog4->setTheta(90.0);

  // Initialize right side logs
  rLog1 = new Log(); rLog1->setPhi(90.0); rLog1->setTheta(90.0);
  rLog2 = new Log(); rLog2->setPhi(90.0); rLog2->setTheta(90.0);
  rLog3 = new Log(); rLog3->setPhi(90.0); rLog3->setTheta(90.0);
  rLog4 = new Log(); rLog4->setPhi(90.0); rLog4->setTheta(90.0);

  // Initialize back side logs
  bLog1 = new Log(); bLog1->setPhi(90.0);
  bLog2 = new Log(); bLog2->setPhi(90.0);
  bLog3 = new Log(); bLog3->setPhi(90.0);
  bLog4 = new Log(); bLog4->setPhi(90.0);
}

// Destructor
Cabin::~Cabin() { }

// setTextureFactor() public member function
// Sets the texture factor (scaling) for the cabin
void Cabin::setTextureFactor(float tf) {texFact = tf;}

// setLogCircularTexture() public overloaded member function
// Sets the texture of the log's circumference
void Cabin::setLogCircularTexture(unsigned int *tex) {
  fLogCircularTexture = tex;
  fLog1->setLogCircularTexture(tex);
  fLog2->setLogCircularTexture(tex);
  fLog3->setLogCircularTexture(tex);
  fLog4->setLogCircularTexture(tex);
  fLog5->setLogCircularTexture(tex);
  fLog6->setLogCircularTexture(tex);
  fLog7->setLogCircularTexture(tex);
  fLog8->setLogCircularTexture(tex);
  fLog9->setLogCircularTexture(tex);

  lLog1->setLogCircularTexture(tex);
  lLog2->setLogCircularTexture(tex);
  lLog3->setLogCircularTexture(tex);
  lLog4->setLogCircularTexture(tex);

  rLog1->setLogCircularTexture(tex);
  rLog2->setLogCircularTexture(tex);
  rLog3->setLogCircularTexture(tex);
  rLog4->setLogCircularTexture(tex);

  bLog1->setLogCircularTexture(tex);
  bLog2->setLogCircularTexture(tex);
  bLog3->setLogCircularTexture(tex);
  bLog4->setLogCircularTexture(tex);
  textureEnabled = true;
}

// setLogTopTexture() public overloaded member function
// Sets the texture of the log's ends
void Cabin::setLogTopTexture(unsigned int *tex) {
  fLogTopTexture = tex;
  fLog1->setLogTopTexture(tex);
  fLog2->setLogTopTexture(tex);
  fLog3->setLogTopTexture(tex);
  fLog4->setLogTopTexture(tex);
  fLog5->setLogTopTexture(tex);
  fLog6->setLogTopTexture(tex);
  fLog7->setLogTopTexture(tex);
  fLog8->setLogTopTexture(tex);
  fLog9->setLogTopTexture(tex);

  lLog1->setLogTopTexture(tex);
  lLog2->setLogTopTexture(tex);
  lLog3->setLogTopTexture(tex);
  lLog4->setLogTopTexture(tex);

  rLog1->setLogTopTexture(tex);
  rLog2->setLogTopTexture(tex);
  rLog3->setLogTopTexture(tex);
  rLog4->setLogTopTexture(tex);

  bLog1->setLogTopTexture(tex);
  bLog2->setLogTopTexture(tex);
  bLog3->setLogTopTexture(tex);
  bLog4->setLogTopTexture(tex);
  textureEnabled = true;
}

// draw() public member function
// Contains logic to draw the object
void Cabin::draw() {
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

  // Size & position fLogs for cabin's front fascia
  fLog1->setLength(lUnit); fLog1->translate(0.0, 0.0, 0.0);
  fLog2->setLength(lUnit); fLog2->translate(0.0, hUnit, 0.0);
  fLog3->setLength(lUnit); fLog3->translate(0.0, hUnit * 2, 0.0);
  fLog4->setLength(lUnit * 6); fLog4->translate(0.0, hUnit * 3, 0.0);
  fLog5->setLength(lUnit * 4); fLog5->translate(0.0, 0.0, lUnit * 2);
  fLog6->setLength(lUnit * 2); fLog6->translate(0.0, hUnit, lUnit * 2);
  fLog7->setLength(lUnit * 2); fLog7->translate(0.0, hUnit * 2, lUnit * 2);
  fLog8->setLength(lUnit); fLog8->translate(0.0, hUnit, lUnit * 5);
  fLog9->setLength(lUnit); fLog9->translate(0.0, hUnit * 2, lUnit * 5);

  // Size & position for cabin's left side
  lLog1->setLength(lUnit * 6); lLog1->translate(-0.1, 0.0, 0.1);
  lLog2->setLength(lUnit * 6); lLog2->translate(-0.1, hUnit, 0.1);
  lLog3->setLength(lUnit * 6); lLog3->translate(-0.1, hUnit * 2, 0.1);
  lLog4->setLength(lUnit * 6); lLog4->translate(-0.1, hUnit * 3, 0.1);

  // Size & position for cabin's right side
  rLog1->setLength(lUnit * 6); rLog1->translate(-0.1, 0.0, (lUnit * 6) - 0.1);
  rLog2->setLength(lUnit * 6); rLog2->translate(-0.1, hUnit, (lUnit * 6) - 0.1);
  rLog3->setLength(lUnit * 6); rLog3->translate(-0.1, hUnit * 2, (lUnit * 6) - 0.1);
  rLog4->setLength(lUnit * 6); rLog4->translate(-0.1, hUnit * 3, (lUnit * 6) - 0.1);

  // Size & position for cabin's back side
  bLog1->setLength(lUnit * 6); bLog1->translate((lUnit * 6) - 0.1, 0.0, 0.0);
  bLog2->setLength(lUnit * 6); bLog2->translate((lUnit * 6) - 0.1, hUnit, 0.0);
  bLog3->setLength(lUnit * 6); bLog3->translate((lUnit * 6) - 0.1, hUnit * 2, 0.0);
  bLog4->setLength(lUnit * 6); bLog4->translate((lUnit * 6) - 0.1, hUnit * 3, 0.0);

  // Draw logs for cabin's front fascia
  fLog1->draw();
  fLog2->draw();
  fLog3->draw();
  fLog4->draw();
  fLog5->draw();
  fLog6->draw();
  fLog7->draw();
  fLog8->draw();
  fLog9->draw();

  // Draw logs for cabin's left side
  lLog1->draw();
  lLog2->draw();
  lLog3->draw();
  lLog4->draw();

  // Draw logs for cabin's right side
  rLog1->draw();
  rLog2->draw();
  rLog3->draw();
  rLog4->draw();

  // Draw logs for cabin's back side
  bLog1->draw();
  bLog2->draw();
  bLog3->draw();
  bLog4->draw();

  // Draw roof, door, and window
  drawRoof();
  drawDoor();
  drawWindow();

  // End
  glPopMatrix();
  if (textureEnabled) {glDisable(GL_TEXTURE_2D);}
}

// drawRoof() private member function
// Draws the pitch roof of the cabin
void Cabin::drawRoof() {
  // Draw front slope
  glBegin(GL_QUADS);
  glVertex3d(-0.2, (hUnit * 4) - 0.15, -0.1);
  glVertex3d(-0.2, (hUnit * 4) - 0.15, (lUnit * 6) + 0.1);
  glVertex3d((lUnit * 3), (hUnit * 5), (lUnit * 6) + 0.1);
  glVertex3d((lUnit * 3), (hUnit * 5), -0.1);
  glEnd();

  // Draw back slope
  glBegin(GL_QUADS);
  glVertex3d((lUnit * 6) + 0.2, (hUnit * 4) - 0.15, -0.1);
  glVertex3d((lUnit * 6) + 0.2, (hUnit * 4) - 0.15, (lUnit * 6) + 0.1);
  glVertex3d((lUnit * 3), (hUnit * 5), (lUnit * 6) + 0.1);
  glVertex3d((lUnit * 3), (hUnit * 5), -0.1);
  glEnd();
}

// drawDoor() private member function
// Draws the front door on the cabin
void Cabin::drawDoor() {
  glBegin(GL_QUADS);
  if (lightingEnabled) {glNormal3d(1.0, 0.0, 0.0);}
  glVertex3d(0.0, -0.1, (lUnit));
  if (lightingEnabled) {glNormal3d(1.0, 0.0, 0.0);}
  glVertex3d(0.0, -0.1, (lUnit * 2));
  if (lightingEnabled) {glNormal3d(1.0, 0.0, 0.0);}
  glVertex3d(0.0, (hUnit * 2) + 0.1, (lUnit * 2));
  if (lightingEnabled) {glNormal3d(1.0, 0.0, 0.0);}
  glVertex3d(0.0, (hUnit * 2) + 0.1, (lUnit));
  glEnd();
}

// drawWindow() private member function
// Draws the front door on the cabin
void Cabin::drawWindow() {
  // Enable emissive lighting
  if (lightingEnabled) {
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shinyFactor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularArray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, wEmissionArray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseArray);
  }

  // Draw window
  glBegin(GL_QUADS);
  if (lightingEnabled) {glNormal3d(1.0, 0.0, 0.0);}
  glVertex3d(0.0, -0.1, (lUnit * 4));
  if (lightingEnabled) {glNormal3d(1.0, 0.0, 0.0);}
  glVertex3d(0.0, -0.1, (lUnit * 5));
  if (lightingEnabled) {glNormal3d(1.0, 0.0, 0.0);}
  glVertex3d(0.0, (hUnit * 2) + 0.1, (lUnit * 4));
  if (lightingEnabled) {glNormal3d(1.0, 0.0, 0.0);}
  glVertex3d(0.0, (hUnit * 2) + 0.1, (lUnit * 5));
  glEnd();
}
