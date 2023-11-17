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
  clock = new AnalogClock();
  lightRain = new LightRain();

  // Enabled lighting
  xyz->enableLighting();
  clock->enableLighting();
  lightRain->enableLighting();
}

// Destructor
Scene::~Scene() {
  delete xyz;
  delete light;
  delete clock;
  delete lightRain;
}

// draw() public member function
// Contains logic to draw the entire scene
void Scene::draw() {
  // Draw the weather scene
  drawWeather();

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

// drawWeather() private member function
// Draws the scene with the current weather conditions
void Scene::drawWeather() {
  lightRain->draw();
  Utilities::errorCheck("Scene::drawWeather()");
}

// drawLandscape() private member function
// Draws the entire landscape
void Scene::drawLandscape() {
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
