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
  rRStep = (rDay[0] - rNight[0]) / 120.0;
  rGStep = (rDay[1] - rNight[1]) / 120.0;
  rBStep = (rDay[2] - rNight[2]) / 120.0;
  tRStep = (rDay[0] - rNight[0]) / 120.0;
  tGStep = (rDay[1] - rNight[1]) / 120.0;
  tBStep = (rDay[2] - rNight[2]) / 120.0;
  sRStep = (sDay[0] - sNight[0]) / 120.0;
  sGStep = (sDay[1] - sNight[1]) / 120.0;
  sBStep = (sDay[2] - sNight[2]) / 120.0;

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

  // Load shaders
  // Mat4Ops::mat4identity(ViewMatrix);
  // snowflakeTexture = Utilities::loadBmp("images/snowflake.bmp");
  // glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  // glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  // snowShader = Utilities::createGeomShaderProgram("shaders/snow.vert", "shaders/snow.geom", "shaders/snow.frag");
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

  // Draw rain or snow
  numPrecip = data->getPrecipDensity();
  weatherCondition = data->getCurrentWeatherCondition();
  if (weatherCondition == 'r') {rain(); fog(0.5);}
  else if (weatherCondition == 't') {rain(); fog(0.65);}
  else if (weatherCondition == 's') {snow(); fog(0.65);}
  else if (weatherCondition == 'm') {mix(); fog(0.65);}

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
    if (weatherCondition == 'r' || weatherCondition == 'm') {
      skyColor[0] = rNight[0] + ((-sunriseDiff + 60) * rRStep);
      skyColor[1] = rNight[1] + ((-sunriseDiff + 60) * rGStep);
      skyColor[2] = rNight[2] + ((-sunriseDiff + 60) * rBStep);
    }
    else if (weatherCondition == 't') {
      int lightning = rand() % lMod;
      if (lightning == lVal) {
        skyColor[0] = 0.8;
        skyColor[1] = 0.8;
        skyColor[2] = 0.8;
      }
      else {
        skyColor[0] = tNight[0] + ((-sunriseDiff + 60) * tRStep);
        skyColor[1] = tNight[1] + ((-sunriseDiff + 60) * tGStep);
        skyColor[2] = tNight[2] + ((-sunriseDiff + 60) * tBStep);
      }
    }
    else if (weatherCondition == 's') {
      skyColor[0] = sNight[0] + ((-sunriseDiff + 60) * sRStep);
      skyColor[1] = sNight[1] + ((-sunriseDiff + 60) * sGStep);
      skyColor[2] = sNight[2] + ((-sunriseDiff + 60) * sBStep);
    }
    lightFactor = skyColor[0] * 100;
    sun();
  }
  else if ((sunriseDiff < 0) && (sunsetDiff > 0) && (abs(sunriseDiff) > 60) && (abs(sunsetDiff > 60))) {
    if (weatherCondition == 'r' || weatherCondition == 'm') {
      skyColor[0] = rDay[0];
      skyColor[1] = rDay[1];
      skyColor[2] = rDay[2];
      lightFactor = 55;
    }
    else if (weatherCondition == 't') {
      int lightning = rand() % lMod;
      if (lightning == lVal) {
        skyColor[0] = 0.8;
        skyColor[1] = 0.8;
        skyColor[2] = 0.8;
      }
      else {
        skyColor[0] = tDay[0];
        skyColor[1] = tDay[1];
        skyColor[2] = tDay[2];
     }
      lightFactor = 27;
    }
    else if (weatherCondition == 's') {
      skyColor[0] = sDay[0];
      skyColor[1] = sDay[1];
      skyColor[2] = sDay[2];
      lightFactor = 88;
    }
    sun();
  }
  else if (abs(sunsetDiff) <= 60) {
    if (weatherCondition == 'r' || weatherCondition == 'm') {
      skyColor[0] = rDay[0] - ((-sunsetDiff + 60) * rRStep);
      skyColor[1] = rDay[1] - ((-sunsetDiff + 60) * rGStep);
      skyColor[2] = rDay[2] - ((-sunsetDiff + 60) * rBStep);
    }
    else if (weatherCondition == 't') {
      int lightning = rand() % lMod;
      if (lightning == lVal) {
        skyColor[0] = 0.8;
        skyColor[1] = 0.8;
        skyColor[2] = 0.8;
      }
      else {
        skyColor[0] = rDay[0] - ((-sunsetDiff + 60) * tRStep);
        skyColor[1] = rDay[1] - ((-sunsetDiff + 60) * tGStep);
        skyColor[2] = rDay[2] - ((-sunsetDiff + 60) * tBStep);
      }
    }
    else if (weatherCondition == 's') {
      skyColor[0] = sDay[0] - ((-sunsetDiff + 60) * sRStep);
      skyColor[1] = sDay[1] - ((-sunsetDiff + 60) * sGStep);
      skyColor[2] = sDay[2] - ((-sunsetDiff + 60) * sBStep);
    }
    lightFactor = skyColor[0] * 100;
    sun();
  }
  else {
    if (weatherCondition == 't') {
      int lightning = rand() % lMod;
      if (lightning == lVal) {
        skyColor[0] = 0.6;
        skyColor[1] = 0.6;
        skyColor[2] = 0.6;
      }
      else {
        skyColor[0] = rNight[0];
        skyColor[1] = rNight[1];
        skyColor[2] = rNight[2];
      }
    }
    else {
      skyColor[0] = rNight[0];
      skyColor[1] = rNight[1];
      skyColor[2] = rNight[2];
    }
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
  // Set lighting properties
  if (lightingEnabled) {
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shinyFactor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colorArray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorArray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularArray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissionArray);
  }
  glEnable(GL_LIGHTING);
  
  for (int i = 0; i < numPrecip; i++) {
    glPushMatrix();
    glColor3f(0.58, 0.67, 0.67);
    glTranslatef(precipPos[i][0], precipPos[i][1], precipPos[i][2]);
    glScaled(0.005, 0.005, 0.005);
    glCallList(rainDrop);
    glPopMatrix();
  }
  glDisable(GL_LIGHTING);
  updatePrecip();
  Utilities::errorCheck("Precipitation::rain()");
}

// snow() private member function
// Animates snowfall
void Precipitation::snow() {
  // Set lighting properties
  if (lightingEnabled) {
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shinyFactor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colorArray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorArray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularArray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissionArray);
  }
  glEnable(GL_LIGHTING);

  // Draw the snow flakes
  for (int i = 0; i < numPrecip; i++) {
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(precipPos[i][0], precipPos[i][1], precipPos[i][2]);
    glScaled(0.005, 0.005, 0.005);
    glCallList(snowFlake);
    glPopMatrix();
  }

  // Update the position of the snow flakes
  updatePrecip();
  glDisable(GL_LIGHTING);
  Utilities::errorCheck("Precipitation::snow()");

  /*glUseProgram(snowShader);

  // Set snowflake texture
  if (snow_vao != 0 ) {
    glBindVertexArray(snow_vao);
  }
  else {
    float snow_data[2];
    snow_data[0] = 0;
    snow_data[1] = 0;
    
    glGenVertexArrays(1, &snow_vao);
    glBindVertexArray(snow_vao);

    unsigned int vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(snow_data), snow_data, GL_STATIC_DRAW);

    int loc = glGetAttribLocation(snowShader, "vertTexture");
    glVertexAttribPointer(loc, 2, GL_FLOAT, 0, 8, (void*)0);
    glEnableVertexAttribArray(loc);
  }

  // Set projection matrix
  int id = glGetUniformLocation(snowShader, "ProjectionMatrix");
  glUniformMatrix4fv(id, 1, 0, ProjectionMatrix);

  // Set ModelView matrix
  float ModelViewMatrix[16];
  Mat4Ops::mat4copy(ModelViewMatrix, ViewMatrix);
  Mat4Ops::mat4translate(ModelViewMatrix, 0.0, 2.5, 0.0);
  id = glGetUniformLocation(snowShader, "ModelViewMatrix");
  glUniformMatrix4fv(id, 1, 0, ModelViewMatrix);

  // Set color
  const float white[] = {1.0, 1.0, 1.0, 1.0};
  id = glGetUniformLocation(snowShader, "inColor");
  glUniform4fv(id, 1, white);

  // Snowflake size in world coordinates
  id = glGetUniformLocation(snowShader, "wX");
  glUniform1f(id, 1.0);
  id = glGetUniformLocation(snowShader, "wY");
  glUniform1f(id, 1.0);

  // Snowflake size in texture coordinates
  id = glGetUniformLocation(snowShader, "tX");
  glUniform1f(id, 1.0);
  id = glGetUniformLocation(snowShader, "tY");
  glUniform1f(id, 1.0);

  // Bind snowflake texture
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glBindTexture(GL_TEXTURE_2D, snowflakeTexture);
  
  // Draw the snowflake
  glDrawArrays(GL_POINTS, 0, 1);
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER,0);

  //  Revert to fixed pipeline
  glUseProgram(0);
  updatePrecip();*/
}

// mix() private member function
// Animates mixed precipitation
void Precipitation::mix() {
  // Set lighting properties
  if (lightingEnabled) {
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shinyFactor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colorArray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorArray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularArray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissionArray);
  }
  glEnable(GL_LIGHTING);

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
  glDisable(GL_LIGHTING);
  updatePrecip();
  Utilities::errorCheck("Precipitation::mix()");
}

// fog() private member function
// Draws fog
void Precipitation::fog(float density) {
  glEnable(GL_FOG);
  glFogf(GL_FOG_MODE, GL_EXP);
  glFogf(GL_FOG_DENSITY, density);
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
    if (weatherCondition == 'r' || weatherCondition == 't') {precipPos[i][1] -= rainFallSpeed;}
    else if (weatherCondition == 's') {
      float xVar = (-0.03) + static_cast<float>(rand())/(RAND_MAX) * (0.02);
      float zVar = (-0.03) + static_cast<float>(rand())/(RAND_MAX) * (0.02);
      precipPos[i][0] += xVar;
      precipPos[i][1] -= snowFallSpeed;
      precipPos[i][2] += zVar;
    }
    else if ((weatherCondition == 'm') && (i % 2 == 0)) {precipPos[i][1] -= rainFallSpeed;}
    else if ((weatherCondition == 'm') && (i % 2 != 0)) {
      float xVar = (-0.03) + static_cast<float>(rand())/(RAND_MAX) * (0.02);
      float zVar = (-0.03) + static_cast<float>(rand())/(RAND_MAX) * (0.02);
      precipPos[i][0] += xVar;
      precipPos[i][1] -= snowFallSpeed;
      precipPos[i][2] += zVar;
    }

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
