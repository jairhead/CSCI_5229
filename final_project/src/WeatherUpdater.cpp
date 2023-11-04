/*
 * File: WeatherUpdater.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the WeatherUpdater class
 */

#include "WeatherUpdater.h"

// Constructor
WeatherUpdater::WeatherUpdater() {
  std::cout << "Init data!" << std::endl;
  data = WeatherData::getInstance();
}

// Destructor
WeatherUpdater::~WeatherUpdater() { }

// thread() public member function
// Used as a looping thread for weather updates
void WeatherUpdater::thread(int loopTime) {
  std::cout << "WeatherUpdater::thread(): beginning loop" << std::endl;
  while(!data->getEnd()) {
    // TODO: implement
    std::cout << "WeatherUpdater::thread(): loop iteration" << std::endl;

    // Sleep
    sleep(loopTime);
  }
}
