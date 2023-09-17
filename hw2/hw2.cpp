/*
 * Simple program to demonstrate generating coordinates
 * using the Lorenz Attractor
 */

#include <stdio.h>
#include <LorenzAttractorHelper.h>
#include <iostream>

// Main
int main(int argc, char *argv[])
{
   // Enter program
   std::cout << "hw2::Main() starting program" << std::endl;

   // Declare LorenzAttractorHelper object
   LorenzAttractorHelper* la = new LorenzAttractorHelper();
   la->helloWorld();

   // Exit program
   std::cout << "hw2::Main(): exiting" << std::endl;
   return 0;
}
