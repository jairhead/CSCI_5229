/*
 *  Shaders - OpenGL 4 style
 *
 *  Demonstrate shaders:
 *    Pixel lighting using OpenGL 4 style
 *    Draw axes in OpenGL 4 style
 *    Draw text in OpenGL 4 style using geometry shader
 *
 *  Key bindings:
 *  p/P        Toggle between orthogonal & perspective projections
 *  s/S        Start/stop light movement
 *  -/+        Decrease/increase light elevation
 *  a          Toggle axes
 *  arrows     Change view angle
 *  PgDn/PgUp  Zoom in and out
 *  0          Reset view angle
 *  ESC        Exit
 */
#include "CSCIx229.h"
#include "mat4.h"
int axes=1;       //  Display axes
int move=1;       //  Move light
int proj=1;       //  Projection type
int th=0;         //  Azimuth of view angle
int ph=0;         //  Elevation of view angle
int fov=55;       //  Field of view (for perspective)
int pi=0;         //  Pi texture
int font=0;       //  Font texture
double asp=1;     //  Aspect ratio
double dim=3.0;   //  Size of world
int zh=90;        //  Light azimuth
float Ylight=2;   //  Light elevation
int shader[]  = {0,0,0}; //  Shader programs
//  Light colors
const float Emission[]  = {0.0,0.0,0.0,1.0};
const float Ambient[]   = {0.3,0.3,0.3,1.0};
const float Diffuse[]   = {1.0,1.0,1.0,1.0};
const float Specular[]  = {1.0,1.0,1.0,1.0};
const float Shinyness[] = {16};
//  Transformation matrixes
float ProjectionMatrix[16];
float ViewMatrix[16];
//  Set lighting parameters using uniforms
float Position[4];

/*
 * Set color
 */
void SetColor(float R,float G,float B)
{
   float color[] = {R,G,B,1.0};
   glColor3f(R,G,B);
   glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color);
}

//  Cube vertex, normal, color and texture data
const float cube_data[] =
{
//  X  Y  Z  W   Nx Ny Nz    R G B A   s t
   //  Front
   +1,+1,+1,+1,   0, 0,+1,   1,0,0,1,  1,1,
   -1,+1,+1,+1,   0, 0,+1,   1,0,0,1,  0,1,
   +1,-1,+1,+1,   0, 0,+1,   1,0,0,1,  1,0,
   -1,+1,+1,+1,   0, 0,+1,   1,0,0,1,  0,1,
   +1,-1,+1,+1,   0, 0,+1,   1,0,0,1,  1,0,
   -1,-1,+1,+1,   0, 0,+1,   1,0,0,1,  0,0,
   //  Back                        
   -1,-1,-1,+1,   0, 0,-1,   0,0,1,1,  1,0,
   +1,-1,-1,+1,   0, 0,-1,   0,0,1,1,  0,0,
   -1,+1,-1,+1,   0, 0,-1,   0,0,1,1,  1,1,
   +1,-1,-1,+1,   0, 0,-1,   0,0,1,1,  0,0,
   -1,+1,-1,+1,   0, 0,-1,   0,0,1,1,  1,1,
   +1,+1,-1,+1,   0, 0,-1,   0,0,1,1,  0,1,
   //  Right                       
   +1,+1,+1,+1,  +1, 0, 0,   1,1,0,1,  0,1,
   +1,-1,+1,+1,  +1, 0, 0,   1,1,0,1,  0,0,
   +1,+1,-1,+1,  +1, 0, 0,   1,1,0,1,  1,1,
   +1,-1,+1,+1,  +1, 0, 0,   1,1,0,1,  0,0,
   +1,+1,-1,+1,  +1, 0, 0,   1,1,0,1,  1,1,
   +1,-1,-1,+1,  +1, 0, 0,   1,1,0,1,  1,0,
   //  Left                        
   -1,+1,+1,+1,  -1, 0, 0,   0,1,0,1,  1,1,
   -1,+1,-1,+1,  -1, 0, 0,   0,1,0,1,  0,1,
   -1,-1,+1,+1,  -1, 0, 0,   0,1,0,1,  1,0,
   -1,+1,-1,+1,  -1, 0, 0,   0,1,0,1,  0,1,
   -1,-1,+1,+1,  -1, 0, 0,   0,1,0,1,  1,0,
   -1,-1,-1,+1,  -1, 0, 0,   0,1,0,1,  0,0,
   //  Top                         
   +1,+1,+1,+1,   0,+1, 0,   0,1,1,1,  1,0,
   +1,+1,-1,+1,   0,+1, 0,   0,1,1,1,  1,1,
   -1,+1,+1,+1,   0,+1, 0,   0,1,1,1,  0,0,
   +1,+1,-1,+1,   0,+1, 0,   0,1,1,1,  1,1,
   -1,+1,+1,+1,   0,+1, 0,   0,1,1,1,  0,0,
   -1,+1,-1,+1,   0,+1, 0,   0,1,1,1,  0,1,
   //  Bottom                      
   -1,-1,-1,+1,   0,-1, 0,   1,0,1,1,  0,0,
   +1,-1,-1,+1,   0,-1, 0,   1,0,1,1,  1,0,
   -1,-1,+1,+1,   0,-1, 0,   1,0,1,1,  0,1,
   +1,-1,-1,+1,   0,-1, 0,   1,0,1,1,  1,0,
   -1,-1,+1,+1,   0,-1, 0,   1,0,1,1,  0,1,
   +1,-1,+1,+1,   0,-1, 0,   1,0,1,1,  1,1,
   };

/*
 *  Draw a cube
 */
static unsigned int cube_vao=0;
static void Cube(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
   //  Select shader
   glUseProgram(shader[0]);

   //  Once initialized, just bind VAO
   if (cube_vao)
      glBindVertexArray(cube_vao);
   //  Initialize VAO and VBO
   else
   {
      //  Create cube VAO to bind attribute arrays
      glGenVertexArrays(1,&cube_vao);
      glBindVertexArray(cube_vao);

      //  Get buffer name
      unsigned int vbo=0;
      glGenBuffers(1,&vbo);
      //  Bind VBO
      glBindBuffer(GL_ARRAY_BUFFER,vbo);
      //  Copy cube data to VBO
      glBufferData(GL_ARRAY_BUFFER,sizeof(cube_data),cube_data,GL_STATIC_DRAW);

      //  Bind arrays
      //  Vertex
      int loc = glGetAttribLocation(shader[0],"Vertex");
      glVertexAttribPointer(loc,4,GL_FLOAT,0,52,(void*) 0);
      glEnableVertexAttribArray(loc);
      //  Normal
      loc = glGetAttribLocation(shader[0],"Normal");
      glVertexAttribPointer(loc,3,GL_FLOAT,0,52,(void*)16);
      glEnableVertexAttribArray(loc);
      //  Color
      loc  = glGetAttribLocation(shader[0],"Color");
      glVertexAttribPointer(loc,4,GL_FLOAT,0,52,(void*)28);
      glEnableVertexAttribArray(loc);
      //  Texture
      loc  = glGetAttribLocation(shader[0],"Texture");
      glVertexAttribPointer(loc,2,GL_FLOAT,0,52,(void*)44);
      glEnableVertexAttribArray(loc);
   }

   //  Set Projection and View Matrix
   int id = glGetUniformLocation(shader[0],"ProjectionMatrix");
   glUniformMatrix4fv(id,1,0,ProjectionMatrix);
   id = glGetUniformLocation(shader[0],"ViewMatrix");
   glUniformMatrix4fv(id,1,0,ViewMatrix);

   //  Create ModelView matrix
   float ModelViewMatrix[16];
   mat4copy(ModelViewMatrix , ViewMatrix);
   mat4translate(ModelViewMatrix , x,y,z);
   mat4rotate(ModelViewMatrix , th,0,1,0);
   mat4scale(ModelViewMatrix , dx,dy,dz);
   id = glGetUniformLocation(shader[0],"ModelViewMatrix");
   glUniformMatrix4fv(id,1,0,ModelViewMatrix);
   //  Create Normal matrix
   float NormalMatrix[9];
   mat3normalMatrix(ModelViewMatrix , NormalMatrix);
   id = glGetUniformLocation(shader[0],"NormalMatrix");
   glUniformMatrix3fv(id,1,0,NormalMatrix);

   //  Set lighting parameters using uniforms
   id = glGetUniformLocation(shader[0],"Position");
   glUniform4fv(id,1,Position);
   id = glGetUniformLocation(shader[0],"Ambient");
   glUniform4fv(id,1,Ambient);
   id = glGetUniformLocation(shader[0],"Diffuse");
   glUniform4fv(id,1,Diffuse);
   id = glGetUniformLocation(shader[0],"Specular");
   glUniform4fv(id,1,Specular);

   //  Set material properties as uniforms
   id = glGetUniformLocation(shader[0],"Ks");
   glUniform4fv(id,1,Specular);
   id = glGetUniformLocation(shader[0],"Ke");
   glUniform4fv(id,1,Emission);
   id = glGetUniformLocation(shader[0],"Shinyness");
   glUniform1f(id,Shinyness[0]);

   //  Bind Pi texture
   glBindTexture(GL_TEXTURE_2D,pi);
   //  Draw Cube
   glDrawArrays(GL_TRIANGLES,0,36);

   //  Release VAO and VBO
   glBindVertexArray(0);
   glBindBuffer(GL_ARRAY_BUFFER,0);
}

/*
 * Draw a character by selecting character from font texture
 *   This uses a geometry shader to billboard the letter
 *   The letter is placed using the ModelView
 */
static unsigned int font_vao=0;
static void Char(float x,float y,float z,float size,unsigned char ch)
{
   //  Font character dimensions
   const float Sw = 9;
   const float Sh = 16;
   //  Font texture dimensions
   const float Sx = 288;
   const float Sy = 128;

   //  Select shader
   glUseProgram(shader[2]);

   //  Once initialized, just bind VAO
   if (font_vao)
      glBindVertexArray(font_vao);
   //  Initialize VAO and VBO
   else
   {
      //  Texture coordinates
      //  Font characters are 9x16 arranged in 32x8 array
      //  Texture size is 288x128
      float font_data[256*2];
      int k=0;
      for (int t=128-Sh;t>=0;t-=Sh)
         for (int s=0;s<288;s+=Sw)
         {
            font_data[k++] = s/Sx;
            font_data[k++] = t/Sy;
         }

      //  Create font VAO to bind attribute arrays
      glGenVertexArrays(1,&font_vao);
      glBindVertexArray(font_vao);

      //  Get buffer name
      unsigned int vbo=0;
      glGenBuffers(1,&vbo);
      //  Bind VBO
      glBindBuffer(GL_ARRAY_BUFFER,vbo);
      //  Copy cube data to VBO
      glBufferData(GL_ARRAY_BUFFER,sizeof(font_data),font_data,GL_STATIC_DRAW);

      //  Bind texture array
      int loc  = glGetAttribLocation(shader[2],"Texture");
      glVertexAttribPointer(loc,2,GL_FLOAT,0,8,(void*)0);
      glEnableVertexAttribArray(loc);
   }

   //  Set Projection Matrix
   int id = glGetUniformLocation(shader[2],"ProjectionMatrix");
   glUniformMatrix4fv(id,1,0,ProjectionMatrix);
   //  Create ModelView matrix
   float ModelViewMatrix[16];
   mat4copy(ModelViewMatrix , ViewMatrix);
   mat4translate(ModelViewMatrix , x,y,z);
   id = glGetUniformLocation(shader[2],"ModelViewMatrix");
   glUniformMatrix4fv(id,1,0,ModelViewMatrix);
   //  Set font color
   const float White[] = {1,1,1,1};
   id = glGetUniformLocation(shader[2],"Kd");
   glUniform4fv(id,1,White);
   //  Character size in world coordinates
   id = glGetUniformLocation(shader[2],"dX");
   glUniform1f(id,Sw*size/Sh);
   id = glGetUniformLocation(shader[2],"dY");
   glUniform1f(id,size);
   //  Character size in texture coordinates
   id = glGetUniformLocation(shader[2],"sX");
   glUniform1f(id,Sw/Sx);
   id = glGetUniformLocation(shader[2],"sY");
   glUniform1f(id,Sh/Sy);

   //  Bind font texture
   glBindTexture(GL_TEXTURE_2D,font);
   //  Draw Character
   glDrawArrays(GL_POINTS,ch,1);

   //  Release VAO and VBO
   glBindVertexArray(0);
   glBindBuffer(GL_ARRAY_BUFFER,0);
}

//  Axes vertex data
const float axes_data[] =
{
   0,0,0,
   2,0,0,
   0,0,0,
   0,2,0,
   0,0,0,
   0,0,2,
};
static unsigned int axes_vao=0;
/*
 * Draw axes
 */
static void Axes()
{
   //  Select shader
   glUseProgram(shader[1]);

   //  Once initialized, just bind VAO
   if (axes_vao)
      glBindVertexArray(axes_vao);
   //  Initialize VAO and VBO
   else
   {
      //  Create axes VAO to bind attribute arrays
      glGenVertexArrays(1,&axes_vao);
      glBindVertexArray(axes_vao);

      //  Get buffer name
      unsigned int vbo=0;
      glGenBuffers(1,&vbo);
      //  Bind VBO
      glBindBuffer(GL_ARRAY_BUFFER,vbo);
      //  Copy cube data to VBO
      glBufferData(GL_ARRAY_BUFFER,sizeof(axes_data),axes_data,GL_STATIC_DRAW);

      //  Bind arrays (vertex only)
      int loc = glGetAttribLocation(shader[1],"Vertex");
      glVertexAttribPointer(loc,3,GL_FLOAT,0,12,(void*) 0);
      glEnableVertexAttribArray(loc);
   }

   //  Set Projection Matrix
   int id = glGetUniformLocation(shader[1],"ProjectionMatrix");
   glUniformMatrix4fv(id,1,0,ProjectionMatrix);
   //  View matrix is the modelview matrix since model matrix is I
   id = glGetUniformLocation(shader[1],"ModelViewMatrix");
   glUniformMatrix4fv(id,1,0,ViewMatrix);
   //  Set color
   const float White[] = {1,1,1,1};
   id = glGetUniformLocation(shader[1],"Kd");
   glUniform4fv(id,1,White);

   //  Draw Axes
   glDrawArrays(GL_LINES,0,6);

   //  Release VAO and VBO
   glBindVertexArray(0);
   glBindBuffer(GL_ARRAY_BUFFER,0);

   //  Label axes (changes shader and VAO)
   Char(2,0,0,0.2,'X');
   Char(0,2,0,0.2,'Y');
   Char(0,0,2,0.2,'Z');
}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);

   //  Create Projection matrix
   mat4identity(ProjectionMatrix);
   if (proj)
      mat4perspective(ProjectionMatrix , fov,asp,dim/16,16*dim);
   else
      mat4ortho(ProjectionMatrix , -dim*asp, +dim*asp, -dim, +dim, -dim, +dim);
   //  Create View matrix
   mat4identity(ViewMatrix);
   if (proj)
   {
      double Ex = -2*dim*Sin(th)*Cos(ph);
      double Ey = +2*dim        *Sin(ph);
      double Ez = +2*dim*Cos(th)*Cos(ph);
      mat4lookAt(ViewMatrix , Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
   }
   else
   {
      mat4rotate(ViewMatrix , ph,1,0,0);
      mat4rotate(ViewMatrix , th,0,1,0);
   }
   //  Light position
   Position[0] = 4*Cos(zh);
   Position[1] = Ylight;
   Position[2] = 4*Sin(zh);
   Position[3] = 1;

   //  Now draw the scene (just a cube for now)
   //  To do other objects create a VBO and VAO for each object
   Cube(0,0,0 , 1,1,1 , 0);

   //  Draw axes
   if (axes) Axes();

   //  Revert to fixed pipeline for labels
   glUseProgram(0);

   //  Display parameters
   glWindowPos2i(5,5);
   Print("Angle=%d,%d  Dim=%.1f Projection=%s",
     th,ph,dim,proj?"Perpective":"Orthogonal");
   //  Render the scene and make it visible
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void idle()
{
   //  Elapsed time in seconds
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   if (move) zh = fmod(90*t,360.0);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
   //  Right arrow key - increase angle by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      th += 5;
   //  Left arrow key - decrease angle by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      th -= 5;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      ph += 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      ph -= 5;
   //  PageUp key - increase dim
   else if (key == GLUT_KEY_PAGE_DOWN)
      dim += 0.1;
   //  PageDown key - decrease dim
   else if (key == GLUT_KEY_PAGE_UP && dim>1)
      dim -= 0.1;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Update projection
   Project(proj?fov:0,asp,dim);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Reset view angle
   else if (ch == '0')
      th = ph = 0;
   //  Toggle axes
   else if (ch == 'a' || ch == 'A')
      axes = 1-axes;
   //  Toggle projection type
   else if (ch == 'p' || ch == 'P')
      proj = 1-proj;
   //  Toggle light movement
   else if (ch == 's' || ch == 'S')
      move = 1-move;
   //  Light elevation
   else if (ch == '+')
      Ylight += 0.1;
   else if (ch == '-')
      Ylight -= 0.1;
   //  Reproject
   Project(proj?fov:0,asp,dim);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, RES*width,RES*height);
   //  Set projection
   Project(proj?fov:0,asp,dim);
}

/*
 *  Read text file
 */
char* ReadText(char *file)
{
   char* buffer;
   //  Open file
   FILE* f = fopen(file,"rt");
   if (!f) Fatal("Cannot open text file %s\n",file);
   //  Seek to end to determine size, then rewind
   fseek(f,0,SEEK_END);
   int n = ftell(f);
   rewind(f);
   //  Allocate memory for the whole file
   buffer = (char*)malloc(n+1);
   if (!buffer) Fatal("Cannot allocate %d bytes for text file %s\n",n+1,file);
   //  Snarf the file
   if (fread(buffer,n,1,f)!=1) Fatal("Cannot read %d bytes for text file %s\n",n,file);
   buffer[n] = 0;
   //  Close and return
   fclose(f);
   return buffer;
}

/*
 *  Print Shader Log
 */
void PrintShaderLog(int obj,char* file)
{
   int len=0;
   glGetShaderiv(obj,GL_INFO_LOG_LENGTH,&len);
   if (len>1)
   {
      int n=0;
      char* buffer = (char *)malloc(len);
      if (!buffer) Fatal("Cannot allocate %d bytes of text for shader log\n",len);
      glGetShaderInfoLog(obj,len,&n,buffer);
      fprintf(stderr,"%s:\n%s\n",file,buffer);
      free(buffer);
   }
   glGetShaderiv(obj,GL_COMPILE_STATUS,&len);
   if (!len) Fatal("Error compiling %s\n",file);
}

/*
 *  Print Program Log
 */
void PrintProgramLog(int obj)
{
   int len=0;
   glGetProgramiv(obj,GL_INFO_LOG_LENGTH,&len);
   if (len>1)
   {
      int n=0;
      char* buffer = (char *)malloc(len);
      if (!buffer) Fatal("Cannot allocate %d bytes of text for program log\n",len);
      glGetProgramInfoLog(obj,len,&n,buffer);
      fprintf(stderr,"%s\n",buffer);
   }
   glGetProgramiv(obj,GL_LINK_STATUS,&len);
   if (!len) Fatal("Error linking program\n");
}

/*
 *  Create Shader
 */
int CreateShader(GLenum type,char* file)
{
   //  Create the shader
   int shader = glCreateShader(type);
   //  Load source code from file
   char* source = ReadText(file);
   glShaderSource(shader,1,(const char**)&source,NULL);
   free(source);
   //  Compile the shader
   fprintf(stderr,"Compile %s\n",file);
   glCompileShader(shader);
   //  Check for errors
   PrintShaderLog(shader,file);
   //  Return name
   return shader;
}

/*
 *  Create Shader Program
 */
int CreateShaderProg(char* VertFile,char* FragFile)
{
   //  Create program
   int prog = glCreateProgram();
   //  Create and compile vertex shader
   int vert = CreateShader(GL_VERTEX_SHADER,VertFile);
   //  Create and compile fragment shader
   int frag = CreateShader(GL_FRAGMENT_SHADER,FragFile);
   //  Attach vertex shader
   glAttachShader(prog,vert);
   //  Attach fragment shader
   glAttachShader(prog,frag);
   //  Link program
   glLinkProgram(prog);
   //  Check for errors
   PrintProgramLog(prog);
   //  Return name
   return prog;
}

/*
 *  Create Shader Program
 */
int CreateShaderGeom(char* VertFile,char* GeomFile,char* FragFile)
{
   //  Create program
   int prog = glCreateProgram();
   //  Compile shaders
   int vert = CreateShader(GL_VERTEX_SHADER  ,VertFile);
   int geom = CreateShader(GL_GEOMETRY_SHADER,GeomFile);
   int frag = CreateShader(GL_FRAGMENT_SHADER,FragFile);
   //  Attach shaders
   glAttachShader(prog,vert);
   glAttachShader(prog,geom);
   glAttachShader(prog,frag);
   //  Link program
   glLinkProgram(prog);
   //  Check for errors
   PrintProgramLog(prog);
   //  Return name
   return prog;
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(600,600);
   glutCreateWindow("Shaders - OpenGL4");
#ifdef USEGLEW
   //  Initialize GLEW
   if (glewInit()!=GLEW_OK) Fatal("Error initializing GLEW\n");
#endif
   //  Set callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   glutIdleFunc(idle);
   //  Load textures
   pi   = LoadTexBMP("pi.bmp");
   font = LoadTexBMP("font.bmp");
   //  Switch font to nearest
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
   //  Create Shader Programs
   shader[0] = CreateShaderProg("gl4pix.vert","gl4pix.frag");
   shader[1] = CreateShaderProg("gl4fix.vert","gl4fix.frag");
   shader[2] = CreateShaderGeom("gl4tex.vert","gl4tex.geom","gl4tex.frag");
   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   return 0;
}
