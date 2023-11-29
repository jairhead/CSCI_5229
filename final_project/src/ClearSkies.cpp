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
  starRStep = (star[0] - day[0]) / 120.0;
  starGStep = (star[1] - day[1]) / 120.0;
  starBStep = (star[2] - day[2]) / 120.0;

  // Stars
  starObj = Utilities::loadOBJ("data/star.obj");
  for (int i = 0; i < numStars; i++) {
    float xVal = (starXMin) + static_cast<float>(rand())/(RAND_MAX) * (starXMax - starXMin);
    float zVal = (starZMin) + static_cast<float>(rand())/(RAND_MAX) * (starZMax - starZMin);
    starPos[i][0] = xVal;
    starPos[i][1] = 2.8;
    starPos[i][2] = zVal;
    int twinkle = rand() % 11;
    if (twinkle == twinkleVal) {twinkles[i] = true;}
    else {twinkles[i] = false;}
  }
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
  fog(0.0);

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
  currHr = data->getHour();
  currMin = data->getMinute();
  sunriseHr = data->getSunriseHour();
  sunriseMin = data->getSunriseMinute();
  sunsetHr = data->getSunsetHour();
  sunsetMin = data->getSunsetMinute();
  
  // Compute differences
  sunriseDiff = Utilities::timeDifference(currHr, currMin, sunriseHr, sunriseMin);
  sunsetDiff = Utilities::timeDifference(currHr, currMin, sunsetHr, sunsetMin);
  daytimeDiff = Utilities::timeDifference(sunriseHr, sunriseMin, sunsetHr, sunsetMin);

  // Handle time of day
  if (abs(sunriseDiff) <= 60) {
    skyColor[0] = night[0] + ((-sunriseDiff + 60) * rStep);
    skyColor[1] = night[1] + ((-sunriseDiff + 60) * gStep);
    skyColor[2] = night[2] + ((-sunriseDiff + 60) * bStep);
    lightFactor = skyColor[0] * 100;
    sunrise();
    stars(3);
  }
  else if ((sunriseDiff < 0) && (sunsetDiff > 0) && (abs(sunriseDiff) > 60) && (abs(sunsetDiff > 60))) {
    skyColor[0] = day[0];
    skyColor[1] = day[1];
    skyColor[2] = day[2];
    lightFactor = 70;
    sun();
  }
  else if (abs(sunsetDiff) <= 60) {
    skyColor[0] = day[0] - ((-sunsetDiff + 60) * rStep);
    skyColor[1] = day[1] - ((-sunsetDiff + 60) * gStep);
    skyColor[2] = day[2] - ((-sunsetDiff + 60) * bStep);
    lightFactor = skyColor[0] * 100;
    sunset();
    stars(1);
  }
  else {
    skyColor[0] = night[0];
    skyColor[1] = night[1];
    skyColor[2] = night[2];
    moon();
    stars(2);
  }

  // Set the sky color and draw
  skyBox->color(skyColor[0], skyColor[1], skyColor[2]);
  skyBox->draw();
  Utilities::errorCheck("ClearSkies::sky()");
}

// sunrise() private member function
// Draws the sunrise
void ClearSkies::sunrise() {
  // If sunriseDiff > 0, it's before the sunrise time (increase the brightness of the sun)
  // Else, begin moving the sun across the sky
  double xPos = orbitDist;
  double yPos = 0.0;
  double zPos = zDist;
  if (sunriseDiff > 0) {
    lightFactor = (60 - sunriseDiff);
    light->setDrawLight(false);
    
  }
  else {
    lightFactor = 60;
    double percentage = ((double)daytimeDiff - sunsetDiff) / (daytimeDiff);
    double th = (percentage) * (180.0);
    xPos = Utilities::cosine(th) * orbitDist;
    yPos = Utilities::sine(th) * orbitDist;
  }

  // Set up light source
  light->setSpecular(0);
  light->setDiffuse(lightFactor);
  light->setAmbient(lightFactor);
  light->init();
  light->translateLight0(xPos, yPos, zPos);
  light->enableLight0();
}

// sun() private member function
// Draws the sun
void ClearSkies::sun() {
  // Calculate the position of the sun
  lightFactor = 60;
  double percentage = ((double)daytimeDiff - sunsetDiff) / (daytimeDiff);
  double th = (percentage) * (180.0);
  double xPos = Utilities::cosine(th) * orbitDist;
  double yPos = Utilities::sine(th) * orbitDist;
  double zPos = zDist;

  // Set up light source
  light->setDrawLight(true);
  light->setSpecular(0);
  light->setDiffuse(lightFactor);
  light->setAmbient(lightFactor);
  light->init();
  light->translateLight0(xPos, yPos, zPos);
  light->enableLight0();
  Utilities::errorCheck("ClearSkies::sun()");
}

// sunset() private member function
// Draws the sunset
void ClearSkies::sunset() {
  // If sunriseDiff > 0, it's before the sunrise time (move the sun across the sky)
  // Else, decrease the brightness of the sun
  double xPos = -orbitDist;
  double yPos = 0.0;
  double zPos = zDist;
  if (sunsetDiff > 0) {
    lightFactor = 60;
    double percentage = ((double)daytimeDiff - sunsetDiff) / (daytimeDiff);
    double th = (percentage) * (180.0);
    xPos = Utilities::cosine(th) * orbitDist;
    yPos = Utilities::sine(th) * orbitDist;
  }
  else {
    lightFactor = (60 + sunriseDiff);
    light->setDrawLight(false);
  }

  // Set up light source
  light->setSpecular(0);
  light->setDiffuse(lightFactor);
  light->setAmbient(lightFactor);
  light->init();
  light->translateLight0(xPos, yPos, zPos);
  light->enableLight0();
}

// moon() private member function
// Draws the moon
void ClearSkies::moon() {
  // Calculate the position of the moon
  lightFactor = 5;
  double percentage = ((double)daytimeDiff - sunriseDiff) / (daytimeDiff);
  double th = (percentage) * (180.0);
  double xPos = Utilities::cosine(th) * orbitDist;
  double yPos = Utilities::sine(th) * orbitDist;
  double zPos = zDist;

  // Set up light source
  light->setDrawLight(true);
  light->setSpecular(0);
  light->setDiffuse(lightFactor);
  light->setAmbient(lightFactor);
  light->init();
  light->translateLight0(xPos, yPos, zPos);
  light->enableLight0();
  Utilities::errorCheck("ClearSkies::moon()");
}

// fog() private member function
// Disables fog
void ClearSkies::fog(float density) {
  glDisable(GL_FOG);
  Utilities::errorCheck("Precipitation::fog()");
}

// stars() private member function
// Draws the stars
void ClearSkies::stars(int timeOfDay) {
  for (int i = 0; i < numStars; i++) {
    // Push the matrix
    glPushMatrix();

    // Set the color of the stars
    // If timeOfDay == 1, then sunset
    // If timeOfDay == 2, then night
    // If timeOfDay == 3, then sunrise
    if (timeOfDay == 1) {
      if (sunsetDiff > 0) {
        starColor[0] = day[0] + ((-sunsetDiff + 60) * starRStep);
        starColor[1] = day[1] + ((-sunsetDiff + 60) * starGStep);
        starColor[2] = day[2] + ((-sunsetDiff + 60) * starBStep);
      }
      else {
        starColor[0] = star[0];
        starColor[1] = star[1];
        starColor[2] = star[2];
      }
    }
    else if (timeOfDay == 2) {
      if (twinkles[i] == true) {
        starColor[0] = static_cast<float>(rand())/(RAND_MAX);
        starColor[1] = static_cast<float>(rand())/(RAND_MAX);
        starColor[2] = static_cast<float>(rand())/(RAND_MAX);
      }
      else {
        starColor[0] = star[0];
        starColor[1] = star[1];
        starColor[2] = star[2];
      }
    }
    else {
      if (sunriseDiff < 0) {
        starColor[0] = star[0] - ((-sunriseDiff + 60) * starRStep);
        starColor[1] = star[1] - ((-sunriseDiff + 60) * starGStep);
        starColor[2] = star[2] - ((-sunriseDiff + 60) * starBStep);
      }
      else {
        starColor[0] = star[0];
        starColor[1] = star[1];
        starColor[2] = star[2];
      }
    }

    // Draw the star
    glColor3f(starColor[0], starColor[1], starColor[2]);
    glTranslatef(starPos[i][0], starPos[i][1], starPos[i][2]);
    glScaled(0.01, 0.01, 0.01);
    glCallList(starObj);
    glPopMatrix();
  }
}
