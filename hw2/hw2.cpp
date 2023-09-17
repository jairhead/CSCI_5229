/*
 * Simple program to demonstrate generating coordinates
 * using the Lorenz Attractor
 */

#include <stdio.h>
#include <LorenzAttractorHelper.h>
#include <iostream>



/*
 *  Main
 */
int main(int argc, char *argv[])
{
   std::cout << "Hello from main!" << std::endl;
   LorenzAttractorHelper* foo = new LorenzAttractorHelper();
   foo->helloWorld();
   return 0;
}
