/*
 * File: Sphere.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the Utilities class
 */

#include "Utilities.h"

// initializeGlew() public member function
// Tries to initialize GLEW (throws a GenericHomeworkException if it fails)
void Utilities::initializeGlew() {
  #ifdef USEGLEW
  if (glewInit() != GLEW_OK) {throw GenericHomeworkException();}
  std::cout << "PrimaryGraphicsHelper::initializeGlew(): GLEW initialization successful!"
            << std::endl;
  #else
  std::cout << "PrimaryGraphicsHelper::initializeGlew(): Skipped GLEW initialization"
            << std::endl;
  #endif
}

// errorCheck() public member function
// Checks errors from OpenGL
void Utilities::errorCheck(std::string where) {
  int error = glGetError();
  if (error) {
    std::cout << "PrimaryGraphicsHelper::errorCheck(): [ERROR] "
              << gluErrorString(error) << ", " << where
              << std::endl;
  }
}

// displayText() public member function
// Displays a string to the scene
void Utilities::displayText(std::string text) {
  #ifdef USEGLEW
  for (size_t i = 0; i < text.size(); i++) {glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);}
  #else
  std::cout << parameters << std::endl;
  #endif
}

// loadBmp() public member function
// Contains logic to load a bitmap image into OpenGL as a texture
unsigned int Utilities::loadBmp(const char* fileName) {
  // Attempt to open the file
  FILE* f = fopen(fileName, "rb");
  if (!f) {std::cout << "Cannot open file." << std::endl; throw GenericHomeworkException();}

  // Check image magic
  unsigned short magic;
  if (fread(&magic,2,1,f)!=1) {std::cout << "Cannot read magic." << std::endl; throw GenericHomeworkException();}
  if (magic!=0x4D42 && magic!=0x424D) {std::cout << "Image magic not BMP." << std::endl; throw GenericHomeworkException();}
  
  // Read header
  unsigned int dx,dy,off,k; // Image dimensions, offset and compression
  unsigned short nbp,bpp;   // Planes and bits per pixel
  if (fseek(f,8,SEEK_CUR) || fread(&off,4,1,f)!=1 ||
      fseek(f,4,SEEK_CUR) || fread(&dx,4,1,f)!=1 || fread(&dy,4,1,f)!=1 ||
      fread(&nbp,2,1,f)!=1 || fread(&bpp,2,1,f)!=1 || fread(&k,4,1,f)!=1) {
    std::cout << "Cannot read header from file." << std::endl;
    throw GenericHomeworkException();
  }

  // reverseBytes bytes on big endian hardware (detected by backwards magic)
  if (magic==0x424D) {
    reverseBytes(&off,4);
    reverseBytes(&dx,4);
    reverseBytes(&dy,4);
    reverseBytes(&nbp,2);
    reverseBytes(&bpp,2);
    reverseBytes(&k,4);
  }

  // Check image parameters
  unsigned int max;
  glGetIntegerv(GL_MAX_TEXTURE_SIZE,(int*)&max);
  if ((dx < 1) || (dx>max)) {std::cout << "Image width " << dx << " out of range 1-" << max << std::endl; throw GenericHomeworkException();}
  if ((dy < 1) || (dy>max)) {std::cout << "Image height " << dy << " out of range 1-" << max << std::endl; throw GenericHomeworkException();}
  if (nbp != 1) {std::cout << "Bit planes is not 1: " << nbp << std::endl; throw GenericHomeworkException();}
  if (bpp != 24) {std::cout << "Bits per pixel is not 24: " << bpp << std::endl; throw GenericHomeworkException();}
  if (k != 0) {std::cout << "Compressed files not supported." << std::endl; throw GenericHomeworkException();}

  // OpenGL 2.0 lifts the restriction that texture size must be a power of two
  #ifndef GL_VERSION_2_0
  for (k = 1; k < dx; k *= 2);
  if (k != dx) {std::cout << "Image width not a power of two: " << dx << std::endl; throw GenericHomeworkException();}
  for (k = 1; k < dy; k *= 2);
  if (k != dy) {std::cout << "Image height not a power of two: " << dy << std::endl; throw GenericHomeworkException();}
  #endif

  // Read image
  unsigned int size = (3 * dx * dy);
  unsigned char* image = (unsigned char*) malloc(size);
  if (!image) {std::cout << "Cannot allocate " << size << " bytes of memory for the image." << std::endl; throw GenericHomeworkException();}
  if (fseek(f,off,SEEK_SET) || (fread(image,size,1,f) != 1)) {std::cout << "Error reading data from image." << std::endl; throw GenericHomeworkException();}
  fclose(f);
  for (k=0;k<size;k+=3) {
    unsigned char temp = image[k];
    image[k]   = image[k+2];
    image[k+2] = temp;
  }

  //  Sanity check and 
  errorCheck("Utilities::loadBmp(): checking image");
  unsigned int texture;
  glGenTextures(1,&texture);
  glBindTexture(GL_TEXTURE_2D,texture);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,dx,dy,0,GL_RGB,GL_UNSIGNED_BYTE,image);
  if (glGetError()) {std::cout << "Error in glTexImage2D " << dx << "x" << dy << std::endl; throw GenericHomeworkException();}
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

  // Free image memory & return texture name
  std::cout << "Utilities::loadBmp(): " << fileName << " loaded successfully." << std::endl;
  free(image);
  return texture;
}

// reverseBytes() private member function
// Contains logic to reverse n bytes
void Utilities::reverseBytes(void* x,const int n) {
  char* ch = (char*)x;
  for (int k = 0; k < (n/2); k++) {
    char tmp = ch[k];
    ch[k] = ch[n-1-k];
    ch[n-1-k] = tmp;
  }
}

// sine() private member function
// Returns the sine of the provided angle in degrees
double Utilities::sine(double angle) {return sin(angle * (3.14159265 / 180));}

// cosine() private member function
// Returns the cosine of the provided angle in degrees
double Utilities::cosine(double angle) {return cos(angle * (3.14159265 / 180));}
