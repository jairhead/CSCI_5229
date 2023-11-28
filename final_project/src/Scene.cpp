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
  clear = new ClearSkies(light);
  precip = new Precipitation(light);

  // Enabled lighting
  xyz->enableLighting();
  precip->enableLighting();
}

// Destructor
Scene::~Scene() {
  delete xyz;
  delete light;
  delete clear;
  delete precip;
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
}

// drawWeather() private member function
// Draws the scene with the current weather conditions
void Scene::drawWeather() {
  // Get current weather condition
  char wc = data->getCurrentWeatherCondition();

  // Draw weather based on current weather
  if (wc == 'n') {clear->draw();}
  if (wc == 'r' || wc == 's' || wc == 'm') {precip->draw();}

  // Check for errors
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

// drawLightOrbit() private member function
// Orbits the light around the y-axis (for testing)
void Scene::drawLightOrbit() {
  // Adjust lightAngle
  lightAngle += lightOrbitInc;
  if (lightAngle > 360) {lightAngle = 0.0;}
  light->init();
  light->translateLight0(lightOrbitRadius * Utilities::cosine(lightAngle),
                         lightHeight,
                         lightOrbitRadius * Utilities::sine(lightAngle));
  light->enableLight0();
  Utilities::errorCheck("Scene::drawLight()");
}
