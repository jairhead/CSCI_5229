/*
 * File: WeatherData.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the WeatherData class
 */

#include "WeatherData.h"

// Initialize instance to nullptr
WeatherData* WeatherData::instance = nullptr;

// Private constructor
WeatherData::WeatherData() { }

// Private destructor
WeatherData::~WeatherData() { }

// getInstance() public member function
// Returns a pointer to the WeatherData instance
WeatherData* WeatherData::getInstance() {
  if (instance == nullptr) {WeatherData::instance = new WeatherData();}
  return WeatherData::instance;
}

// removeInstance() public member function
// Deletes the instance
void WeatherData::removeInstance() {
  if (instance != nullptr) {
    delete instance;
    instance = nullptr;
  }
}

// setLiveWeather() public member function
void WeatherData::setLiveWeather(bool val) {
  std::unique_lock dataLock(dataMutex);
  liveWeather = val;
}

// getLiveWeather() public member function
bool WeatherData::getLiveWeather() {
  std::unique_lock dataLock(dataMutex);
  bool returnVal = liveWeather;
  return returnVal;
}

// setExit() public member function
void WeatherData::setExit(bool val) {
  std::unique_lock dataLock(dataMutex);
  exit = val;
}

// getExit() public member function
bool WeatherData::getExit() {
  std::unique_lock dataLock(dataMutex);
  bool returnVal = exit;
  return returnVal;
}

// setHour() public member function
void WeatherData::setHour(int val) {
  if (val < 1) {val = 1;}
  else if (val > 23) {val = 23;}
  std::unique_lock dataLock(dataMutex);
  hour = val;
}

// getHour() public member function
int WeatherData::getHour() {
  std::unique_lock dataLock(dataMutex);
  int returnVal = hour;
  return returnVal;
}

// setMinute() public member function
void WeatherData::setMinute(int val) {
  if (val < 0) {val = 0;}
  else if (val > 59) {val = 59;}
  std::unique_lock dataLock(dataMutex);
  minute = val;
}

// getMinute() public member function
int WeatherData::getMinute() {
  std::unique_lock dataLock(dataMutex);
  int returnVal = minute;
  return returnVal;
}

// setSunriseHour() public member function
void WeatherData::setSunriseHour(int val) {
  if (val < 1) {val = 1;}
  else if (val > 23) {val = 23;}
  std::unique_lock dataLock(dataMutex);
  sunriseHour = val;
}

// getSunriseHour() public member function
int WeatherData::getSunriseHour() {
  std::unique_lock dataLock(dataMutex);
  int returnVal = sunriseHour;
  return returnVal;
}

// setSunriseMinute() public member function
void WeatherData::setSunriseMinute(int val) {
  if (val < 0) {val = 0;}
  else if (val > 59) {val = 59;}
  std::unique_lock dataLock(dataMutex);
  sunriseMinute = val;
}

// getSunriseMinute() public member function
int WeatherData::getSunriseMinute() {
  std::unique_lock dataLock(dataMutex);
  int returnVal = sunriseMinute;
  return returnVal;
}

// setSunsetHour() public member function
void WeatherData::setSunsetHour(int val) {
  if (val < 1) {val = 1;}
  else if (val > 23) {val = 23;}
  std::unique_lock dataLock(dataMutex);
  sunsetHour = val;
}

// getSunsetHour() public member function
int WeatherData::getSunsetHour() {
  std::unique_lock dataLock(dataMutex);
  int returnVal = sunsetHour;
  return returnVal;
}

// setSunsetMinute() public member function
void WeatherData::setSunsetMinute(int val) {
  if (val < 0) {val = 0;}
  else if (val > 59) {val = 59;}
  std::unique_lock dataLock(dataMutex);
  sunsetMinute = val;
}

// getSunsetMinute() public member function
int WeatherData::getSunsetMinute() {
  std::unique_lock dataLock(dataMutex);
  int returnVal = sunsetMinute;
  return returnVal;
}

// setSeason() public member function
// 1 = winter
// 2 = spring
// 3 = summer
// 4 = fall
void WeatherData::setSeason(int seas) {
  if (seas < 1) {seas = 1;}
  if (seas > 4) {seas = 4;}
  std::unique_lock dataLock(dataMutex);
  season = seas;
}

// getSeason() public member function
int WeatherData::getSeason() {
  std::unique_lock dataLock(dataMutex);
  int returnVal = season;
  return returnVal;
}
