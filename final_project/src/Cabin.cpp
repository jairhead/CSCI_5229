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

  // Initialize front porch items
  board1 = new RectangularPrism();
  board2 = new RectangularPrism();
  board3 = new RectangularPrism();
  pLog1 = new Log();
  pLog2 = new Log();
  pLog3 = new Log();
  pLog4 = new Log();
  pLog5 = new Log();
}

// Destructor
Cabin::~Cabin() { }

// setTextureFactor() public member function
// Sets the texture factor (scaling) for the cabin
void Cabin::setTextureFactor(float tf) {texFact = tf;}

// setLogCircularTexture() public member function
// Sets the texture of the log's circumference
void Cabin::setLogCircularTexture(unsigned int *tex) {
  logCircularTexture = tex;
  setCircularTextureOfWood(logCircularTexture);
  textureEnabled = true;
}

// setSnowyLogCircularTexture() public member function
// Sets the snowy texture of the log's circumference
void Cabin::setSnowyCircularTextureOfWood(unsigned int *tex) {
  snowyLogCircularTexture = tex;
  textureEnabled = true;
}

// setLogTopTexture() public member function
// Sets the texture of the log's ends
void Cabin::setLogTopTexture(unsigned int *tex) {
  logTopTexture = tex;
  setTopTextureOfWood(logTopTexture);
  textureEnabled = true;
}

// setCircularTextureOfLogs() public member function
// Sets the circular textures of the logs and boards
void Cabin::setCircularTextureOfWood(unsigned int *tex) {
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

  board1->setTexture(tex); board1->enableTexture();
  board2->setTexture(tex); board2->enableTexture();
  board3->setTexture(tex); board3->enableTexture();

  pLog1->setLogCircularTexture(tex);
  pLog2->setLogCircularTexture(tex);
  pLog3->setLogCircularTexture(tex);
  pLog4->setLogCircularTexture(tex);
  pLog5->setLogCircularTexture(tex);
}

// setTopTextureOfWood() public member function
// Sets the top texture of the logs
void Cabin::setTopTextureOfWood(unsigned int *tex) {
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

  pLog1->setLogTopTexture(tex);
  pLog2->setLogTopTexture(tex);
  pLog3->setLogTopTexture(tex);
  pLog4->setLogTopTexture(tex);
  pLog5->setLogTopTexture(tex);
}

// setFrontDoorTexture() public member function
// Sets the texture of the cabin's front door
void Cabin::setFrontDoorTexture(unsigned int *tex) {
  frontDoorTexture = tex;
  textureEnabled = true;
}

// setRoofTexture() public member function
// Sets the texture of the cabin's roof
void Cabin::setRoofTexture(unsigned int *tex) {
  roofTexture = tex;
  textureEnabled = true;
}

// setSnowyRoofTexture() public member function
// Sets the texture of the cabin's snowy roof
void Cabin::setSnowyRoofTexture(unsigned int *tex) {
  snowyRoofTexture = tex;
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

  // Set the texture
  char weatherCondition = data->getCurrentWeatherCondition();
  if (weatherCondition == 's' || weatherCondition == 'm') {
    setCircularTextureOfWood(snowyLogCircularTexture);
  }
  else {
    setCircularTextureOfWood(logCircularTexture);
  }

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
  drawPorch();

  // End
  glPopMatrix();
  if (textureEnabled) {glDisable(GL_TEXTURE_2D);}
}

// drawRoof() private member function
// Draws the pitch roof of the cabin
void Cabin::drawRoof() {
  // Set texture
  if (textureEnabled) {
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, *roofTexture);
  }

  // Draw front slope
  glBegin(GL_QUADS);
  if (textureEnabled) {glTexCoord2f(5.0, 0.0);}
  glVertex3d(-0.2, (hUnit * 4) - 0.15, -0.1);
  if (textureEnabled) {glTexCoord2f(0.0, 0.0);}
  glVertex3d(-0.2, (hUnit * 4) - 0.15, (lUnit * 6) + 0.1);
  if (textureEnabled) {glTexCoord2f(0.0, 5.0);}
  glVertex3d((lUnit * 3), (hUnit * 5), (lUnit * 6) + 0.1);
  if (textureEnabled) {glTexCoord2f(5.0, 5.0);}
  glVertex3d((lUnit * 3), (hUnit * 5), -0.1);
  glEnd();

  // Draw back slope
  glBegin(GL_QUADS);
  if (textureEnabled) {glTexCoord2f(5.0, 0.0);}
  glVertex3d((lUnit * 6) + 0.2, (hUnit * 4) - 0.15, -0.1);
  if (textureEnabled) {glTexCoord2f(0.0, 0.0);}
  glVertex3d((lUnit * 6) + 0.2, (hUnit * 4) - 0.15, (lUnit * 6) + 0.1);
  if (textureEnabled) {glTexCoord2f(0.0, 5.0);}
  glVertex3d((lUnit * 3), (hUnit * 5), (lUnit * 6) + 0.1);
  if (textureEnabled) {glTexCoord2f(5.0, 5.0);}
  glVertex3d((lUnit * 3), (hUnit * 5), -0.1);
  glEnd();
  if (textureEnabled) {glDisable(GL_TEXTURE_2D);}
}

// drawDoor() private member function
// Draws the front door on the cabin
void Cabin::drawDoor() {
  // Set texture
  if (textureEnabled) {
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, *frontDoorTexture);
  }

  // Bottom right point
  glBegin(GL_QUADS);
  if (lightingEnabled) {glNormal3d(1.0, 0.0, 0.0);}
  if (textureEnabled) {glTexCoord2f(0.0, 0.0);}
  glVertex3d(0.0, -0.1, (lUnit));

  // Bottom left point
  if (lightingEnabled) {glNormal3d(1.0, 0.0, 0.0);}
  if (textureEnabled) {glTexCoord2f(1.0, 0.0);}
  glVertex3d(0.0, -0.1, (lUnit * 2));

  // Top left point
  if (lightingEnabled) {glNormal3d(1.0, 0.0, 0.0);}
  if (textureEnabled) {glTexCoord2f(1.0, 1.0);}
  glVertex3d(0.0, (hUnit * 2) + 0.1, (lUnit * 2));

  // Top right point
  if (lightingEnabled) {glNormal3d(1.0, 0.0, 0.0);}
  if (textureEnabled) {glTexCoord2f(0.0, 1.0);}
  glVertex3d(0.0, (hUnit * 2) + 0.1, (lUnit));
  glEnd();
  if (textureEnabled) {glDisable(GL_TEXTURE_2D);}
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
  glVertex3d(0.0, (hUnit * 2) + 0.1, (lUnit * 5));
  if (lightingEnabled) {glNormal3d(1.0, 0.0, 0.0);}
  glVertex3d(0.0, (hUnit * 2) + 0.1, (lUnit * 4));
  glEnd();
}

// drawWindow() private member function
// Draws the front porch of the cabin
void Cabin::drawPorch() {
  // Size & position boards
  board1->scale(0.5, 0.1, lUnit * 4.5);
  board1->translate(-0.2, -0.05, lUnit * 3.0);
  board2->scale(0.5, 0.1, lUnit * 4.5);
  board2->translate(-0.5, -0.05, lUnit * 3.0);
  board3->scale(0.5, 0.1, lUnit * 4.5);
  board3->translate(-0.8, -0.05, lUnit * 3.0);

  // Size & position hand rail logs
  pLog1->setLength(lUnit);
  pLog1->setRadius(0.04);
  pLog1->translate(-0.84, 0.0, 0.3);
  pLog2->setLength(lUnit * 4);
  pLog2->setRadius(0.02);
  pLog2->setPhi(90.0);
  pLog2->translate(-0.84, 0.12, 0.3);
  pLog3->setLength(lUnit * 4);
  pLog3->setRadius(0.02);
  pLog3->setPhi(90.0);
  pLog3->setTheta(90.0);
  pLog3->translate(-0.84, 0.12, 0.2);
  pLog4->setLength(lUnit);
  pLog4->setRadius(0.04);
  pLog4->translate(-0.84, 0.0, 1.3);
  pLog5->setLength(lUnit * 4);
  pLog5->setRadius(0.02);
  pLog5->setPhi(90.0);
  pLog5->setTheta(90.0);
  pLog5->translate(-0.84, 0.12, 1.3);

  // Draw
  board1->draw();
  board2->draw();
  board3->draw();
  pLog1->draw();
  pLog2->draw();
  pLog3->draw();
  pLog4->draw();
  pLog5->draw();
}
