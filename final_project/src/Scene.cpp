/*
 * File: Scene.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the Scene class
 */

#include "Scene.h"

// Constructor
Scene::Scene() {
  // Get pointer to data structure
  data = WeatherData::getInstance();

  // Allocate objects
  xyz = new Axes();
  light = new LightManager();
  sky = new SkyBox();
  clock = new AnalogClock();

  // Enabled lighting
  xyz->enableLighting();
  sky->enableLighting();
  clock->enableLighting();
}

// Destructor
Scene::~Scene() {
  delete xyz;
  delete light;
  delete sky;
  delete clock;
}

// draw() public member function
// Contains logic to draw the entire scene
void Scene::draw() {
  // Draw the sky & landscape
  drawSky();
  drawLandscape();

  // Draw the axes
  if (drawAxes) {
    xyz->draw();
    Utilities::errorCheck("PrimaryGraphicsHelper::display(): axes");
  }

  // Draw the clock
  clock->draw();

  // Draw the sun
  data->setHour(8);
  data->setMinute(20);
  drawLight();
}

// drawSky() private member function
// Draws the sky box and sets its color
void Scene::drawSky() {
  // Position the sun or moon
  drawLight();
  Utilities::errorCheck("Scene::drawSky(): sun / moon");

  // Draw the sky box
  sky->color(0.0,0.24,0.76);
  sky->scale(3.0, 3.0, 3.0);
  sky->draw();
  Utilities::errorCheck("Scene::drawSky(): sky box");
}

// drawLandscape() private member function
// Draws the entire landscape
void Scene::drawLandscape() {
  /*grass->scale(2.0, 0.01, 2.0);
  grass->translate(0.0, 0.0, 0.0);
  grass->color(0.14,0.82,0.0);
  grass->draw();*/

  Utilities::errorCheck("Scene::drawLandscape()");
}

// drawLight() private member function
// Draws the sun / moon in position
void Scene::drawLight() {
  // Get the current hour
  int hour = data->getHour();
  int minute = data->getMinute();
  double th = (minute * 0.25);
  if (hour != 12) {th += (hour * 15.0);}

  // Create the light source
  double xPos = Utilities::cosine(th) * 1.8;
  double yPos = Utilities::sine(th) * 1.8;
  double zPos = -1.5;
  if (th < 180.0) {light->setDrawColor(1.0, 0.97, 0.0);}
  else {light->setDrawColor(0.70, 0.70, 0.70);}
  light->init();
  light->translateLight0(xPos, yPos, zPos);
  light->enableLight0();

  Utilities::errorCheck("Scene::drawLight()");
}
