/*
 * File: LorenzAttractorHelper.h
 * Author: Jared McKneely
 * Description: Main runtime for Homework #2 (CSCI 5229)
 */

#include <stdio.h>
#include <LorenzAttractorHelper.h>
#include <iostream>

// Main
int main(int argc, char *argv[])
{
   // Enter program
   std::cout << "hw2::main() starting program" << std::endl;

   // Declare LorenzAttractorHelper object
   LorenzAttractorHelper* la = new LorenzAttractorHelper();

   // Initialize GLUT w/ user args, double buffer
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
   glutInitWindowSize(500, 500);
   glutCreateWindow("Coordinates");

   // Pass callback methods to GLUT
   glutDisplayFunc(la->display);
   glutReshapeFunc(la->reshape);
   glutSpecialFunc(la->special);
   glutKeyboardFunc(la->key);

   // Exit program
   std::cout << "hw2::main(): exiting program" << std::endl;
   return 0;
}
