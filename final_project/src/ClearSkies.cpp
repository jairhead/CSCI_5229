/*
 * File: ClearSkies.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the ClearSkies class, a child class
 *              of the BaseWeatherCondition abstract class.
 */

#include "ClearSkies.h"

// Default Constructor
ClearSkies::ClearSkies(LightManager* l) {
  // Get pointer to data structure
  data = WeatherData::getInstance();

  // Initialize objects
  skyBox = new SkyBox();
  land = new Landscape();
  light = l;

  // Enable lighting
  land->enableLighting();

  // Compute steps
  rStep = (day[0] - night[0]) / 120.0;
  gStep = (day[1] - night[1]) / 120.0;
  bStep = (day[2] - night[2]) / 120.0;
}

// Destructor
ClearSkies::~ClearSkies() {
  delete skyBox;
  delete land;
}

// draw() public member function
// Contains logic to draw the weather condition
void ClearSkies::draw() {
  // Save transformation and set up; Translate -> Rotate -> Scale
  glPushMatrix();
  glTranslated(posArray[0], posArray[1], posArray[2]);
  glRotated(theta, 0, 1, 0);
  glScaled(scaleArray[0], scaleArray[1], scaleArray[2]);

  // Draw landscape and sky
  landscape();
  sky();

  // End
  glPopMatrix();
}

// landscape() private member function
// Draws the landscape
void ClearSkies::landscape() {
  land->translate(-0.5, 0.0, -0.5);
  land->scale(0.25, 0.25, 0.25);
  land->draw();
}

// sky() private member function
// Draws the sky
void ClearSkies::sky() {
  // Scale sky
  skyBox->scale(5.0, 5.0, 5.0);

  // Get times
  int currHr = data->getHour();
  int currMin = data->getMinute();
  int sunriseHr = data->getSunriseHour();
  int sunriseMin = data->getSunriseMinute();
  int sunsetHr = data->getSunsetHour();
  int sunsetMin = data->getSunsetMinute();
  
  // Compute differences
  int sunriseDiff = Utilities::timeDifference(currHr, currMin, sunriseHr, sunriseMin);
  int sunsetDiff = Utilities::timeDifference(currHr, currMin, sunsetHr, sunsetMin);

  // Handle time of day
  if (abs(sunriseDiff) <= 60) {
    skyColor[0] = night[0] + ((-sunriseDiff + 60) * rStep);
    skyColor[1] = night[1] + ((-sunriseDiff + 60) * gStep);
    skyColor[2] = night[2] + ((-sunriseDiff + 60) * bStep);
    lightFactor = skyColor[0] * 100;
    sun();
  }
  else if ((sunriseDiff < 0) && (sunsetDiff > 0) && (abs(sunriseDiff) > 60) && (abs(sunsetDiff > 60))) {
    // Set sky color
    skyColor[0] = day[0];
    skyColor[1] = day[1];
    skyColor[2] = day[2];
    lightFactor = 55;
    sun();
  }
  else if (abs(sunsetDiff) <= 60) {
    skyColor[0] = day[0] - ((-sunsetDiff + 60) * rStep);
    skyColor[1] = day[1] - ((-sunsetDiff + 60) * gStep);
    skyColor[2] = day[2] - ((-sunsetDiff + 60) * bStep);
    lightFactor = skyColor[0] * 100;
    sun();
  }
  else {
    skyColor[0] = night[0];
    skyColor[1] = night[1];
    skyColor[2] = night[2];
    moon();
  }

  // Set the sky color and draw
  skyBox->color(skyColor[0], skyColor[1], skyColor[2]);
  skyBox->draw();
  Utilities::errorCheck("ClearSkies::sky()");
}

// sun() private member function
// Draws the sun
void ClearSkies::sun() {
  // Initialize the light source
  light->setDrawLight(false);
  light->setSpecular(0);
  light->setDiffuse(lightFactor);
  light->setAmbient(lightFactor);
  light->init();

  // Set position and enable light source
  light->translateLight0(0.0, 1.8, 0.0);
  light->enableLight0();
  Utilities::errorCheck("ClearSkies::sun()");
}

// moon() private member function
// Draws the moon
void ClearSkies::moon() {
  // Initialize the light source
  light->setDrawLight(false);
  light->setSpecular(0);
  light->setDiffuse(0);
  light->setAmbient(0);
  light->init();

  // Set position and enable light source
  light->translateLight0(0.0, 1.8, 0.0);
  light->enableLight0();
  Utilities::errorCheck("ClearSkies::moon()");
}
