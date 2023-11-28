/*
 * File: Precipitation.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the Precipitation class, a child class
 *              of the BaseWeatherCondition abstract class.
 */

#include "Precipitation.h"

// Default Constructor
Precipitation::Precipitation(LightManager* l) {
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

  // Initialize precipitation
  rainDrop = Utilities::loadOBJ("data/rainDrop.obj");
  snowFlake = Utilities::loadOBJ("data/snowFlake.obj");
  for (int i = 0; i < numPrecip; i++) {
    float xVal = (precipXMin) + static_cast<float>(rand())/(RAND_MAX) * (precipXMax - precipXMin);
    float yVal = (precipYMin) + static_cast<float>(rand())/(RAND_MAX) * (precipYMax - precipYMin);
    float zVal = (precipZMin) + static_cast<float>(rand())/(RAND_MAX) * (precipZMax - precipZMin);
    precipPos[i][0] = xVal;
    precipPos[i][1] = yVal;
    precipPos[i][2] = zVal;
  }
}

// Destructor
Precipitation::~Precipitation() {
  delete skyBox;
  delete land;
}

// draw() public member function
// Contains logic to draw the weather condition
void Precipitation::draw() {
  // Save transformation and set up; Translate -> Rotate -> Scale
  glPushMatrix();
  glTranslated(posArray[0], posArray[1], posArray[2]);
  glRotated(theta, 0, 1, 0);
  glScaled(scaleArray[0], scaleArray[1], scaleArray[2]);

  // Draw landscape, sky, and fog
  landscape();
  sky();
  fog();

  // Draw rain or snow
  numPrecip = data->getPrecipDensity();
  weatherCondition = data->getCurrentWeatherCondition();
  if (weatherCondition == 'r') {rain();}
  else if (weatherCondition == 's') {snow();}
  else if (weatherCondition == 'm') {mix();}

  // End
  glPopMatrix();
}

// landscape() private member function
// Draws the landscape
void Precipitation::landscape() {
  land->translate(-0.5, 0.0, -0.5);
  land->scale(0.25, 0.25, 0.25);
  land->draw();
}

// sky() private member function
// Draws the sky
void Precipitation::sky() {
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
  Utilities::errorCheck("Precipitation::sky()");
}

// sun() private member function
// Draws the sun
void Precipitation::sun() {
  // Initialize the light source
  light->setDrawLight(false);
  light->setSpecular(0);
  light->setDiffuse(lightFactor);
  light->setAmbient(lightFactor);
  light->init();

  // Set position and enable light source
  light->translateLight0(0.0, 1.8, 0.0);
  light->enableLight0();
  Utilities::errorCheck("Precipitation::sun()");
}

// moon() private member function
// Draws the moon
void Precipitation::moon() {
  // Initialize the light source
  light->setDrawLight(false);
  light->setSpecular(0);
  light->setDiffuse(0);
  light->setAmbient(0);
  light->init();

  // Set position and enable light source
  light->translateLight0(0.0, 1.8, 0.0);
  light->enableLight0();
  Utilities::errorCheck("Precipitation::moon()");
}

// rain() private member function
// Animates rainfall
void Precipitation::rain() {
  for (int i = 0; i < numPrecip; i++) {
    glPushMatrix();
    glColor3f(0.58, 0.67, 0.67);
    glTranslatef(precipPos[i][0], precipPos[i][1], precipPos[i][2]);
    glScaled(0.01, 0.01, 0.01);
    glCallList(rainDrop);
    glPopMatrix();
  }
  updatePrecip();
  Utilities::errorCheck("Precipitation::rain()");
}

// snow() private member function
// Animates snowfall
void Precipitation::snow() {
  for (int i = 0; i < numPrecip; i++) {
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(precipPos[i][0], precipPos[i][1], precipPos[i][2]);
    glScaled(0.01, 0.01, 0.01);
    glCallList(snowFlake);
    glPopMatrix();
  }
  updatePrecip();
  Utilities::errorCheck("Precipitation::snow()");
}

// mix() private member function
// Animates mixed precipitation
void Precipitation::mix() {
  for (int i = 0; i < numPrecip; i++) {
    if (i % 2 == 0) {
      glPushMatrix();
      glColor3f(0.58, 0.67, 0.67);
      glTranslatef(precipPos[i][0], precipPos[i][1], precipPos[i][2]);
      glScaled(0.01, 0.01, 0.01);
      glCallList(rainDrop);
      glPopMatrix();
    }
    else {
      glPushMatrix();
      glColor3f(1.0, 1.0, 1.0);
      glTranslatef(precipPos[i][0], precipPos[i][1], precipPos[i][2]);
      glScaled(0.01, 0.01, 0.01);
      glCallList(snowFlake);
      glPopMatrix();
    }
  }
  updatePrecip();
  Utilities::errorCheck("Precipitation::mix()");
}

// fog() private member function
// Draws fog
void Precipitation::fog() {
  glEnable(GL_FOG);
  glFogf(GL_FOG_MODE, GL_EXP);
  glFogf(GL_FOG_DENSITY, 0.50);
  glFogfv(GL_FOG_COLOR, skyColor);
  glFogf(GL_FOG_START, 0);
  glFogf(GL_FOG_END, 1);
  Utilities::errorCheck("Precipitation::fog()");
}

// updatePrecip() private member function
// Updates the position of the rain drops or snow flakes
void Precipitation::updatePrecip() {
  for (int i = 0; i < numPrecip; i++) {
    // Determine which fall speed to use (rain or snow)
    if (weatherCondition == 'r') {precipPos[i][1] -= rainFallSpeed;}
    else if (weatherCondition == 's') {precipPos[i][1] -= snowFallSpeed;}
    else if ((weatherCondition == 'm') && (i % 2 == 0)) {precipPos[i][1] -= rainFallSpeed;}
    else if ((weatherCondition == 'm') && (i % 2 != 0)) {precipPos[i][1] -= snowFallSpeed;}

    // Replace rain drops and snow flakes that hacve reached the bottom
    if (precipPos[i][1] < precipYMin) {
      float xVal = (precipXMin) + static_cast<float>(rand())/(RAND_MAX) * (precipXMax - precipXMin);
      float yVal = (precipYMin) + static_cast<float>(rand())/(RAND_MAX) * (precipYMax - precipYMin);
      float zVal = (precipZMin) + static_cast<float>(rand())/(RAND_MAX) * (precipZMax - precipZMin);
      precipPos[i][0] = xVal;
      precipPos[i][1] = yVal;
      precipPos[i][2] = zVal;
    }
  }
}
