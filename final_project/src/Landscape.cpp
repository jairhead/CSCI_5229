/*
 * File: Landscape.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the Landscape class, a child class
 *              of the BaseObject abstract class.
 */

#include "Landscape.h"

// Default Constructor
Landscape::Landscape() {
  // Get pointer to data structure
  data = WeatherData::getInstance();

  // Load blender objects
  grassValley = Utilities::loadOBJ("data/hillyGrassValley.obj");
  mountainRim = Utilities::loadOBJ("data/mountainRim.obj");
  mountainSnow = Utilities::loadOBJ("data/mountainSnow.obj");

  // Load textures
  textures[0] = Utilities::loadBmp("images/tree-branch-512x512.bmp");
  textures[1] = Utilities::loadBmp("images/fir-leaves-512x512.bmp");
  textures[2] = Utilities::loadBmp("images/snowy-fir-leaves-512x512.bmp");
  textures[3] = Utilities::loadBmp("images/log-circular-512x512.bmp");
  textures[4] = Utilities::loadBmp("images/log-top-512x512.bmp");
  textures[5] = Utilities::loadBmp("images/front-door-512x512.bmp");
  textures[6] = Utilities::loadBmp("images/roof-512x512.bmp");
  textures[7] = Utilities::loadBmp("images/snowy-log-circular-512x512.bmp");
  textures[8] = Utilities::loadBmp("images/snowy-roof-512x512.bmp");

  // Instantiate clock face
  clock = new AnalogClock();
  clock->enableLighting();
  clock->translate(2.3, 1.1, 6.7);
  clock->scale(0.25, 0.25, 0.25);

  // Instantiate trees
  tree = new ConiferousTree();
  tree->setTrunkTexture(&textures[0]);
  tree->setLeafTexture(&textures[1]);
  tree->setSnowyLeafTexture(&textures[2]);
  tree->enableLighting();
  tree->translate(1.5, 1.2, 7.7);
  tree->scale(0.1, 0.1, 0.1);

  // Instantiate cabin
  cabin = new Cabin();
  cabin->setLogCircularTexture(&textures[3]);
  cabin->setLogTopTexture(&textures[4]);
  cabin->setFrontDoorTexture(&textures[5]);
  cabin->setRoofTexture(&textures[6]);
  cabin->setSnowyCircularTextureOfWood(&textures[7]);
  cabin->setSnowyRoofTexture(&textures[8]);
  cabin->enableLighting();
  cabin->rotate(270.0);
  cabin->translate(2.8, 1.3, 7.9);
  cabin->scale(0.75, 0.75, 0.75);
}

// Destructor
Landscape::~Landscape() {
  delete clock;
  delete tree;
}

// color() public member function
// Sets the object's color values
void Landscape::color(float r, float g, float b) {
  colorArray[0] = r;
  colorArray[1] = g;
  colorArray[2] = b;
}

// setTextureFactor() public member function
// Sets the texture factor (scaling) for the object
void Landscape::setTextureFactor(float tf) {texFact = tf;}

// draw() public member function
// Contains logic to draw the object
void Landscape::draw() {
  // Set lighting properties
  if (lightingEnabled) {
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shinyFactor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colorArray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorArray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularArray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissionArray);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
  }

  // Save transformation; Translate -> Rotate -> Scale
  glPushMatrix();
  glTranslated(posArray[0], posArray[1], posArray[2]);
  glRotated(theta, 0, 1, 0);
  glScaled(scaleArray[0], scaleArray[1], scaleArray[2]);

  // Draw the grass landscape using elevation data
  char weatherCondition = data->getCurrentWeatherCondition();
  if (weatherCondition == 's') {glColor3f(0.95, 0.95, 0.95);}
  else {glColor3f(0.04, 0.33, 0);}
  glCallList(grassValley);

  // Draw the mountains
  glTranslated(0.0, -0.1, 0.0);
  if (weatherCondition == 's') {glColor3f(0.95, 0.95, 0.95);}
  else {glColor3f(0.21, 0.21, 0.21);}
  glCallList(mountainRim);

  // Draw the mountain snow
  if (weatherCondition == 'n' || weatherCondition == 'r' || weatherCondition == 't') {glColor3f(0.21, 0.21, 0.21);}
  else {glColor3f(1.0, 1.0, 1.0);}
  glTranslated(0.0, -0.1, 0.0);
  glCallList(mountainSnow);

  // Draw the clock pole
  clock->draw();

  // Draw the trees
  //tree->draw();

  // Draw the cabin
  cabin->draw();

  // End
  glPopMatrix();
}
