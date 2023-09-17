/*
 * File: LorenzAttractorHelper.h
 * Description: Header file for the LorenzAttractorHelper object
 */

#include <stdio.h>
#include <iostream>

class LorenzAttractorHelper {
  public:
    LorenzAttractorHelper();
    ~LorenzAttractorHelper();
    void helloWorld();
  private:
    // Lorenz Parameters
    const double s  = 10;
    const double b  = 2.6666;
    const double r  = 28;
};
