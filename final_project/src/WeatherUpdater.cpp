/*
 * File: WeatherUpdater.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the WeatherUpdater class
 */

#include "WeatherUpdater.h"

// Constructor
WeatherUpdater::WeatherUpdater() {
  data = WeatherData::getInstance();
}

// Destructor
WeatherUpdater::~WeatherUpdater() { }

// demoThread() public member function
// Used to demo all the weather conditions
void WeatherUpdater::demoThread() {
  std::cout << "WeatherUpdater::thread(): beginning loop" << std::endl;
  while(!data->getExit()) {
    // Get the current conditions
    int hour = data->getHour();
    int minute = data->getMinute();
    char weatherCondition = data->getCurrentWeatherCondition();

    // Update time and weather condition
    minute += 5;
    if (minute >= 60) {
      // Reset the minute
      minute = minute % 60;
      data->setMinute(minute);

      // Handle the hour
      hour += 1;
      if (hour > 23) {
        data->setHour(0);
      }
      else {
        data->setHour(hour);
      }

      // Handle weather condition update
      if (hour == 5 && minute == 0) {
        demoIncrementWeatherCondition(weatherCondition);
      }
    }
    else {
      data->setHour(hour);
      data->setMinute(minute);
    }

    // Sleep
    usleep(50000);
  }
}

// demoIncrementWeatherCondition() public member function
// Used to iterate through weather conditions in a demo scenario
void WeatherUpdater::demoIncrementWeatherCondition(char &wc) {
  if (wc == 'n') {
    data->setCurrentWeatherCondition('r');
    int density = rand() % 1000;
    data->setPrecipDensity(density);
    data->setFahrenheit(68);
  }
  else if (wc == 'r') {
    data->setCurrentWeatherCondition('t');
    data->setPrecipDensity(1000);
    data->setFahrenheit(65);
  }
  else if (wc == 't') {
    data->setCurrentWeatherCondition('m');
    int density = rand() % 1000;
    data->setPrecipDensity(density);
    data->setFahrenheit(31);
  }
  else if (wc == 'm') {
    data->setCurrentWeatherCondition('s');
    data->setPrecipDensity(1000);
    data->setFahrenheit(23);
  }
  else if (wc == 's') {
    data->setCurrentWeatherCondition('p');
    data->setFahrenheit(75);
  }
  else if (wc == 'p') {
    data->setCurrentWeatherCondition('n');
    data->setFahrenheit(78);
  }
}
