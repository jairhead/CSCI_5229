/*
 * File: Utilities.cpp
 * Author: Jared McKneely
 * Description: Implementation file for the Utilities class
 */

#include "Utilities.h"

//  Material structure
typedef struct {
  char* name;                 //  Material name
  float Ka[4],Kd[4],Ks[4],Ns; //  Colors and shininess
  float d;                    //  Transparency
  int map;                    //  Texture
} mtl_t;

//  Material count and array
static int Nmtl=0;
static mtl_t* mtl=NULL;

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
  std::cout << text << std::endl;
  #endif
}

// loadBmp() public member function
// Contains logic to load a bitmap image into OpenGL as a texture
unsigned int Utilities::loadBmp(const char* fileName) {
  // Attempt to open the file
  FILE* f = fopen(fileName, "rb");
  if (!f) {std::cout << "Utilities::loadBmp(): cannot open file." << std::endl; throw GenericHomeworkException();}

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

// reverseBytes() public member function
// Contains logic to reverse n bytes
void Utilities::reverseBytes(void* x,const int n) {
  char* ch = (char*)x;
  for (int k = 0; k < (n/2); k++) {
    char tmp = ch[k];
    ch[k] = ch[n-1-k];
    ch[n-1-k] = tmp;
  }
}

// sine() public member function
// Returns the sine of the provided angle in degrees
double Utilities::sine(double angle) {return sin(angle * (3.14159265 / 180));}

// cosine() public member function
// Returns the cosine of the provided angle in degrees
double Utilities::cosine(double angle) {return cos(angle * (3.14159265 / 180));}

// loadElevationData() public member function
// Loads a plaintext elevation data file and returns a 2D double array
double** Utilities::loadElevationData(std::string fileName) {
  // File strings
  std::ifstream file(fileName);
  std::string line;
  std::string token;

  // Min and max values
  int numPoints = 0;
  double xMin = 180.0;
  double xMax = -180.0;
  double yMin = 180.0;
  double yMax = -180.0;

  // Initial read: get x and y bounds
  if (file.is_open()){
    while (std::getline(file, line)) {
      // Make stringstream, toss out first token
      std::stringstream ss(line);
      std::getline(ss, token, '\t');
      std::cout.precision(20);

      // Skip over title
      if (token == "type") {continue;}

      // Get latitude
      std::getline(ss, token, '\t');
      double lat = std::stod(token);
      if (lat < xMin) {xMin = lat;}
      if (lat > xMax) {xMax = lat;}

      // Get longitude
      std::getline(ss, token, '\t');
      double lon = std::stod(token);
      if (lon < yMin) {yMin = lon;}
      if (lon > yMax) {yMax = lon;}
      numPoints++;
    }
  }

  // Get square root of numPoints
  int dim = std::sqrt(numPoints);
  double xFact = (dim) / (xMax - xMin);
  double yFact = (dim) / (yMax - yMin);
  double** dataPtr = new double*[dim];
  for (int i = 0; i < dim; i++) {dataPtr[i] = new double[dim];}

  // Second read: populate data
  file.clear();
  file.seekg(0);
  if (file.is_open()) {
    while (std::getline(file, line)) {
      // Make stringstream, toss out first token
      std::stringstream ss(line);
      std::getline(ss, token, '\t');
      std::cout.precision(20);

      // Skip over title
      if (token == "type") {continue;}

      // Get latitude
      std::getline(ss, token, '\t');
      double lat = std::stod(token);
      int x = (xFact) * (lat - xMin);
      if (x > (dim - 1)) {x = (dim - 1);}
      if (x < 0) {x = 0;}

      // Get longitude
      std::getline(ss, token, '\t');
      double lon = std::stod(token);
      int y = (yFact) * (lon - yMin);
      if (y > (dim - 1)) {y = (dim - 1);}
      if (y < 0) {y = 0;}

      // Get elevation
      std::getline(ss, token, '\t');
      double elev = std::stod(token);
      dataPtr[x][y] = (elev) / (1000.0);
    }
  }
  return dataPtr;
}

// loadOBJ() public member function
// Loads an object from a .obj file type
int Utilities::loadOBJ(const char* fileName) {
  int  Nv,Nn,Nt;  //  Number of vertex, normal and textures
  int  Mv,Mn,Mt;  //  Maximum vertex, normal and textures
  float* V;       //  Array of vertexes
  float* N;       //  Array of normals
  float* T;       //  Array if textures coordinates
  char*  line;    //  Line pointer
  char*  str;     //  String pointer

  //  Open file
  FILE* f = fopen(fileName,"r");
  if (!f) {
    std::cout << "Utilities::loadOBJ(): cannot open file." << std::endl;
    throw GenericHomeworkException();
  }

  // Reset materials
  mtl = NULL;
  Nmtl = 0;

  //  Start new displaylist; push attributes for textures
  int list = glGenLists(1);
  glNewList(list,GL_COMPILE);
  glPushAttrib(GL_ENABLE_BIT|GL_TEXTURE_BIT);

  //  Read vertexes and facets
  V  = N  = T  = NULL;
  Nv = Nn = Nt = 0;
  Mv = Mn = Mt = 0;

  while ((line = readLine(f))) {
    if (line[0]=='v' && line[1]==' ') {readCoord(line+2,3,&V,&Nv,&Mv);}
    else if (line[0]=='v' && line[1] == 'n') {readCoord(line+2,3,&N,&Nn,&Mn);}
    else if (line[0]=='v' && line[1] == 't') {readCoord(line+2,2,&T,&Nt,&Mt);}
    else if (line[0]=='f') {
      line++;
      
      // Read vertex/texture/normal triplets
      glBegin(GL_POLYGON);
      while ((str = getWord(&line))) {
        int Kv,Kt,Kn;
        if (sscanf(str,"%d/%d/%d",&Kv,&Kt,&Kn)==3) {
          if (Kv<0 || Kv>Nv/3) {
            std::cout << "Vertex " << Kv << " out of range 1-" << Nn/3 << std::endl;
            throw GenericHomeworkException();
          }
          if (Kn<0 || Kn>Nn/3) {
            std::cout << "Normal " << Kn << " out of range 1-" << Nn/3 << std::endl;
            throw GenericHomeworkException();
          }
          if (Kt<0 || Kt>Nt/2) {
            std::cout << "Texture " << Kt << " out of range 1-" << Nt/2 << std::endl;
            throw GenericHomeworkException();
          }
        }
        else if (sscanf(str,"%d//%d",&Kv,&Kn)==2) {
          if (Kv<0 || Kv>Nv/3) {
            std::cout << "Vertex " << Kv << " out of range 1-" << Nv/3 << std::endl;
            throw GenericHomeworkException();
          }
          if (Kn<0 || Kn>Nn/3) {
            std::cout << "Normal " << Kn << " out of range 1-" << Nn/3 << std::endl;
            throw GenericHomeworkException();
          }
          Kt = 0;
        }
        else if (sscanf(str,"%d",&Kv)==1)
        {
          if (Kv<0 || Kv>Nv/3) {
            std::cout << "Vertex " << Kv << " out of range 1-" << Nv/3 << std::endl;
            throw GenericHomeworkException();
          }
          Kn = 0;
          Kt = 0;
        }
        else {
          std::cout << "Invalid facet " << str << std::endl;
          throw GenericHomeworkException();
        }

        //  Draw vectors
        if (Kt) glTexCoord2fv(T+2*(Kt-1));
        if (Kn) glNormal3fv(N+3*(Kn-1));
        if (Kv) glVertex3fv(V+3*(Kv-1));
      }
      glEnd();
    }
    //  Use material
    else if ((str = readStr(line,"usemtl"))) {
      setMaterial(str);
    }
    //  Load materials
    else if ((str = readStr(line,"mtllib"))) {
      loadMaterial(str);
    }
    //  Skip this line
  }
  fclose(f);
  //  Pop attributes (textures)
   glPopAttrib();
   glEndList();

   //  Free materials
   for (int k=0;k<Nmtl;k++)
      free(mtl[k].name);
   free(mtl);

   //  Free arrays
   free(V);
   free(T);
   free(N);

   return list;
}

// timeDifference() public member function
// Returns the difference between two times in minutes
int Utilities::timeDifference(int time1Hr, int time1Min, int time2Hr, int time2Min) {
  int minDifference = 0;
  minDifference += (60) * (time2Hr - time1Hr);
  minDifference += (time2Min - time1Min);
  return minDifference;
}

// computeNormal() public member function
// Computes the normal of two vectors (i.e. the cross product)
void Utilities::computeNormal(double vec1[3], double vec2[3], double normal[3]) {
  normal[0] = (vec1[1] * vec2[2]) - (vec1[2] * vec2[1]);
  normal[1] = -((vec1[0] * vec2[2]) - (vec1[2] * vec2[0]));
  normal[2] = (vec1[0] * vec2[1]) - (vec1[1] * vec2[0]);
}

// loadMaterial() private member function
// Loads materials from file
void Utilities::loadMaterial(const char* fileName) {
  int k=-1;
  char* line;
  char* str;

  //  Open file or return with warning on error
  FILE* f = fopen(fileName,"r");
  if (!f) {
    std::cout << "Utilities::loadMaterial(): cannot open file." << std::endl;
    throw GenericHomeworkException();
  }

  //  Read lines
  while ((line = readLine(f))) {
    //  New material
    if ((str = readStr(line,"newmtl"))) {
      int l = strlen(str);
      //  Allocate memory for structure
      k = Nmtl++;
      mtl = (mtl_t*)realloc(mtl,Nmtl*sizeof(mtl_t));
      //  Store name
      mtl[k].name = (char*)malloc(l+1);
      if (!mtl[k].name) {
        std::cout << "Cannot allocate " << (l+1) << " for name" << std::endl;
        throw GenericHomeworkException();
      }
      strcpy(mtl[k].name,str);
      //  Initialize materials
      mtl[k].Ka[0] = mtl[k].Ka[1] = mtl[k].Ka[2] = 0;   mtl[k].Ka[3] = 1;
      mtl[k].Kd[0] = mtl[k].Kd[1] = mtl[k].Kd[2] = 0;   mtl[k].Kd[3] = 1;
      mtl[k].Ks[0] = mtl[k].Ks[1] = mtl[k].Ks[2] = 0;   mtl[k].Ks[3] = 1;
      mtl[k].Ns  = 0;
      mtl[k].d   = 0;
      mtl[k].map = 0;
    }
    //  If no material short circuit here
    else if (k<0) {}
    //  Ambient color
    else if (line[0]=='K' && line[1]=='a')
      readFloat(line+2,3,mtl[k].Ka);
    //  Diffuse color
    else if (line[0]=='K' && line[1] == 'd')
      readFloat(line+2,3,mtl[k].Kd);
    //  Specular color
    else if (line[0]=='K' && line[1] == 's')
      readFloat(line+2,3,mtl[k].Ks);
    //  Material Shininess
    else if (line[0]=='N' && line[1]=='s') {
      readFloat(line+2,1,&mtl[k].Ns);
      //  Limit to 128 for OpenGL
      if (mtl[k].Ns>128) {mtl[k].Ns = 128;}
    }
    //  Textures (must be BMP - will fail if not)
    else if ((str = readStr(line,"map_Kd"))) {
      mtl[k].map = loadBmp(str);
    }
    //  Ignore line if we get here
  }
  fclose(f);
}

// setMaterial() private member function
// Loads materials from file
void Utilities::setMaterial(const char* name) {
  //  Search materials for a matching name
  for (int k=0; k < Nmtl; k++) {
    if (!strcmp(mtl[k].name, name)) {
      //  Set material colors
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mtl[k].Ka);
      glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mtl[k].Kd);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mtl[k].Ks);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &mtl[k].Ns);
      //  Bind texture if specified
      if (mtl[k].map) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, mtl[k].map);
      }
      else {
        glDisable(GL_TEXTURE_2D);
      }
      return;
    }
  }
   //  No matches
   fprintf(stderr,"Unknown material %s\n",name);
}

// readCoord() private member function
// Reads coordinates that are provided
void Utilities::readCoord(char* line,int n,float* x[],int* N,int* M) {
  //  Allocate memory if necessary
  if (*N+n > *M) {
    *M += 8192;
    *x = (float*)realloc(*x,(*M)*sizeof(float));
    if (!*x) {
      std::cout << "Cannot allocate memory" << std::endl;
      throw GenericHomeworkException();
    }
  }

  //  Read n coordinates
  readFloat(line,n,(*x)+*N);
  (*N)+=n;
}

// readFloat() private member function
// Reads n floats
void Utilities::readFloat(char* line, int n, float x[]) {
  for (int i=0;i<n;i++) {
    char* str = getWord(&line);
    if (!str) {
      std::cout << "Premature EOL reading " << n << " floats" << std::endl;
      throw GenericHomeworkException();
    }
    if (sscanf(str,"%f",x+i)!=1) {
      std::cout << "Error reading float " << i << std::endl;
      throw GenericHomeworkException();
    }
  }
}

// readLine() private member function
// Returns pointer to line or NULL on EOF
static int linelen=0;    //  Length of line
static char* line=NULL;  //  Internal storage for line
char* Utilities::readLine(FILE* f) {
  char ch;  //  Character read
  int k=0;  //  Character count
  while ((ch = fgetc(f)) != EOF) {
    //  Allocate more memory for long strings
    if (k>=linelen) {
      linelen += 8192;
      line = (char*)realloc(line,linelen);
      if (!line) {
        std::cout << "Out of memory in readLine()" << std::endl;
        throw GenericHomeworkException();
      }
    }

    //  End of Line
    if (CRLF(ch)) {
      // Eat extra CR or LF characters (if any)
      while ((ch = fgetc(f)) != EOF) {
        if (!CRLF(ch)) {break;}
      }

      //  Stick back the overrun
      if (ch != EOF) ungetc(ch,f);
        
      //  Bail
      break;
    }
    //  Pad character to line
    else {
      line[k++] = ch;
    }
  }
  
  //  Terminate line if anything was read
  if (k>0) {
    line[k] = 0;
  }

  //  Return pointer to line or NULL on EOF
  return k>0 ? line : NULL;
}

// readStr() private member function
// Reads a string conditionally
char* Utilities::readStr(char* line, const char* skip) {
  // Check for a match on the skip string
  while (*skip && *line && *skip==*line) {
    skip++;
    line++;
  }

  // Skip must be NULL for a match
  if (*skip || !isspace(*line)) {
    return NULL;
  }
  
  // Read string
  return getWord(&line);
}

// getWord() private member function
// Reads to next non-whitespace word
char* Utilities::getWord(char** line) {
  //  Skip leading whitespace
  while (**line && isspace(**line)) {
    (*line)++;
  }
  if (!**line) {return NULL;}

  //  Start of word
  char* word = *line;

  //  Read until next whitespace
  while (**line && !isspace(**line)) {
    (*line)++;
  }

  //  Mark end of word if not NULL
  if (**line) {
    **line = 0;
    (*line)++;
  }
  return word;
}

// CRLF() private member function
// Return true if CR or LF
int Utilities::CRLF(char ch) {
  return ch == '\r' || ch == '\n';
}
