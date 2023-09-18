/*
 * File: hw2.cpp
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
   LorenzAttractorHelper::printLorenzAttractorParameters();

   // Initialize GLUT w/ user args, double buffer
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
   glutInitWindowSize(500, 500);
   glutCreateWindow("Homework 2");

   // Pass callback methods to GLUT
   glutDisplayFunc(LorenzAttractorHelper::display);
   glutReshapeFunc(LorenzAttractorHelper::reshape);
   glutSpecialFunc(LorenzAttractorHelper::special);
   glutKeyboardFunc(LorenzAttractorHelper::key);

   // Call GLUT main loop
   glutMainLoop();

   // Exit program
   std::cout << "hw2::main(): exiting program" << std::endl;
   return 0;
}
