/*
 *  3D Objects
 *
 *  Demonstrates how to draw objects in 3D.
 *
 *  Key bindings:
 *  m/M        Cycle through different sets of objects
 *  a          Toggle axes
 *  arrows     Change view angle
 *  0          Reset view angle
 *  ESC        Exit
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#ifdef USEGLEW
#include <GL/glew.h>
#endif
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
// Tell Xcode IDE to not gripe about OpenGL deprecation
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#else
#include <GL/glut.h>
#endif
//  Default resolution
//  For Retina displays compile with -DRES=2
#ifndef RES
#define RES 1
#endif

int th=0;          //  Azimuth of view angle
int ph=0;          //  Elevation of view angle
double zh=0;       //  Rotation of teapot
int axes=1;        //  Display axes
int mode=0;        //  What to display
const char* text[] = {"Cuboids","Spheres","FlatPlane Outline","FlatPlane Fill","SolidPlane","Icosahedron DrawElements","Icosahedron DrawArrays","Icosahedron VBO","Scene"};

//  Cosine and Sine in degrees
#define Cos(x) (cos((x)*3.14159265/180))
#define Sin(x) (sin((x)*3.14159265/180))

/*
 *  Convenience routine to output raster text
 *  Use VARARGS to make this more flexible
 */
#define LEN 8192  //  Maximum length of text string
void Print(const char* format , ...)
{
   char    buf[LEN];
   char*   ch=buf;
   va_list args;
   //  Turn the parameters into a character string
   va_start(args,format);
   vsnprintf(buf,LEN,format,args);
   va_end(args);
   //  Display the characters one at a time at the current raster position
   while (*ch)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}

/*
 *  Check for OpenGL errors
 */
void ErrCheck(const char* where)
{
   int err = glGetError();
   if (err) fprintf(stderr,"ERROR: %s [%s]\n",gluErrorString(err),where);
}

/*
 *  Print message to stderr and exit
 */
void Fatal(const char* format , ...)
{
   va_list args;
   va_start(args,format);
   vfprintf(stderr,format,args);
   va_end(args);
   exit(1);
}

/*
 *  Draw a cube
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
static void cube(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
   //  Save transformation
   glPushMatrix();
   //  Offset
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);
   //  Cube
   glBegin(GL_QUADS);
   //  Front
   glColor3f(1,0,0);
   glVertex3f(-1,-1, 1);
   glVertex3f(+1,-1, 1);
   glVertex3f(+1,+1, 1);
   glVertex3f(-1,+1, 1);
   //  Back
   glColor3f(0,0,1);
   glVertex3f(+1,-1,-1);
   glVertex3f(-1,-1,-1);
   glVertex3f(-1,+1,-1);
   glVertex3f(+1,+1,-1);
   //  Right
   glColor3f(1,1,0);
   glVertex3f(+1,-1,+1);
   glVertex3f(+1,-1,-1);
   glVertex3f(+1,+1,-1);
   glVertex3f(+1,+1,+1);
   //  Left
   glColor3f(0,1,0);
   glVertex3f(-1,-1,-1);
   glVertex3f(-1,-1,+1);
   glVertex3f(-1,+1,+1);
   glVertex3f(-1,+1,-1);
   //  Top
   glColor3f(0,1,1);
   glVertex3f(-1,+1,+1);
   glVertex3f(+1,+1,+1);
   glVertex3f(+1,+1,-1);
   glVertex3f(-1,+1,-1);
   //  Bottom
   glColor3f(1,0,1);
   glVertex3f(-1,-1,-1);
   glVertex3f(+1,-1,-1);
   glVertex3f(+1,-1,+1);
   glVertex3f(-1,-1,+1);
   //  End
   glEnd();
   //  Undo transformations
   glPopMatrix();
}

/*
 *  Draw vertex in polar coordinates
 */
static void Vertex(double th,double ph)
{
   glColor3f(Cos(th)*Cos(th) , Sin(ph)*Sin(ph) , Sin(th)*Sin(th));
   glVertex3d(Sin(th)*Cos(ph) , Sin(ph) , Cos(th)*Cos(ph));
}

/*
 *  Draw a sphere (version 1)
 *     at (x,y,z)
 *     radius (r)
 */
static void sphere1(double x,double y,double z,double r)
{
   const int d=15;

   //  Save transformation
   glPushMatrix();
   //  Offset and scale
   glTranslated(x,y,z);
   glScaled(r,r,r);

   //  South pole cap
   glBegin(GL_TRIANGLE_FAN);
   Vertex(0,-90);
   for (int th=0;th<=360;th+=d)
   {
      Vertex(th,d-90);
   }
   glEnd();

   //  Latitude bands
   for (int ph=d-90;ph<=90-2*d;ph+=d)
   {
      glBegin(GL_QUAD_STRIP);
      for (int th=0;th<=360;th+=d)
      {
         Vertex(th,ph);
         Vertex(th,ph+d);
      }
      glEnd();
   }

   //  North pole cap
   glBegin(GL_TRIANGLE_FAN);
   Vertex(0,90);
   for (int th=0;th<=360;th+=d)
   {
      Vertex(th,90-d);
   }
   glEnd();

   //  Undo transformations
   glPopMatrix();
}

/*
 *  Draw a sphere (version 2)
 *     at (x,y,z)
 *     radius (r)
 */
static void sphere2(double x,double y,double z,double r)
{
   const int d=15;

   //  Save transformation
   glPushMatrix();
   //  Offset and scale
   glTranslated(x,y,z);
   glScaled(r,r,r);

   //  Latitude bands
   for (int ph=-90;ph<90;ph+=d)
   {
      glBegin(GL_QUAD_STRIP);
      for (int th=0;th<=360;th+=d)
      {
         Vertex(th,ph);
         Vertex(th,ph+d);
      }
      glEnd();
   }

   //  Undo transformations
   glPopMatrix();
}

/*
 *  Draw a airplane shaped polygon at (x,y,z)
 */
static void FlatPlane(int type,double x,double y,double z)
{
   //  Save transformation
   glPushMatrix();
   //  Offset
   glTranslated(x,y,z);
   //  Fuselage and wings
   glColor3f(1,1,0); 
   glBegin(type);
   glVertex2f( 1.0, 0.0);
   glVertex2f( 0.8, 0.1);
   glVertex2f( 0.0, 0.1);
   glVertex2f(-1.0, 0.5);
   glVertex2f(-1.0,-0.5);
   glVertex2f( 0.0,-0.1);
   glVertex2f( 0.8,-0.1);
   glEnd();
   //  Vertical tail
   glColor3f(1,0,0);
   glBegin(type);
   glVertex3f(-1.0, 0.0,0.0);
   glVertex3f(-1.0, 0.0,0.5);
   glVertex3f(-0.5, 0.0,0.0);
   glEnd();
   //  Undo transformations
   glPopMatrix();
}

/*
 *  Draw solid airplane
 *    at (x,y,z)
 *    nose towards (dx,dy,dz)
 *    up towards (ux,uy,uz)
 */
static void SolidPlane(double x,double y,double z,
                       double dx,double dy,double dz,
                       double ux,double uy, double uz)
{
   // Dimensions used to size airplane
   const double wid=0.05;
   const double nose=+0.50;
   const double cone= 0.20;
   const double wing= 0.00;
   const double strk=-0.20;
   const double tail=-0.50;
   //  Unit vector in direction of flght
   double D0 = sqrt(dx*dx+dy*dy+dz*dz);
   double X0 = dx/D0;
   double Y0 = dy/D0;
   double Z0 = dz/D0;
   //  Unit vector in "up" direction
   double D1 = sqrt(ux*ux+uy*uy+uz*uz);
   double X1 = ux/D1;
   double Y1 = uy/D1;
   double Z1 = uz/D1;
   //  Cross product gives the third vector
   double X2 = Y0*Z1-Y1*Z0;
   double Y2 = Z0*X1-Z1*X0;
   double Z2 = X0*Y1-X1*Y0;
   //  Rotation matrix
   double mat[16];
   mat[0] = X0;   mat[4] = X1;   mat[ 8] = X2;   mat[12] = 0;
   mat[1] = Y0;   mat[5] = Y1;   mat[ 9] = Y2;   mat[13] = 0;
   mat[2] = Z0;   mat[6] = Z1;   mat[10] = Z2;   mat[14] = 0;
   mat[3] =  0;   mat[7] =  0;   mat[11] =  0;   mat[15] = 1;

   //  Save current transforms
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glMultMatrixd(mat);
   //  Nose
   glColor3f(0,0,1);
   glBegin(GL_TRIANGLE_FAN);
   glVertex3d(nose, 0.0, 0.0);
   for (int th=0;th<=360;th+=30)
      glVertex3d(cone,wid*Cos(th),wid*Sin(th));
   glEnd();
   //  Fuselage
   glBegin(GL_QUAD_STRIP);
   for (int th=0;th<=360;th+=30)
   {
      glVertex3d(cone,wid*Cos(th),wid*Sin(th));
      glVertex3d(tail,wid*Cos(th),wid*Sin(th));
   }
   glEnd();
   // Tailpipe
   glBegin(GL_TRIANGLE_FAN);
   glVertex3d(tail, 0.0, 0.0);
   for (int th=0;th<=360;th+=30)
      glVertex3d(tail,wid*Cos(th),wid*Sin(th));
   glEnd();
   //  Wings
   glColor3f(1,1,0);
   glBegin(GL_TRIANGLES);
   glVertex3d(wing, 0.0, wid);
   glVertex3d(tail, 0.0, wid);
   glVertex3d(tail, 0.0, 0.5);

   glVertex3d(wing, 0.0,-wid);
   glVertex3d(tail, 0.0,-wid);
   glVertex3d(tail, 0.0,-0.5);
   glEnd();
   //  Vertical tail
   glColor3f(1,0,0);
   glBegin(GL_TRIANGLES);
   glVertex3d(strk, 0.0, 0.0);
   glVertex3d(tail, 0.3, 0.0);
   glVertex3d(tail, 0.0, 0.0);
   glEnd();
   //  Undo transformations
   glPopMatrix();
}

/*
 *  Draw icosahedron using glDrawElements
 *     at (x,y,z)
 *     size  s
 *     rotated th about the x axis
 */
static void icosahedron1(float x,float y,float z,float s,float th)
{
   //  Vertex index list
   const int N=60;
   const unsigned char index[] =
      {
       2, 1, 0,    3, 2, 0,    4, 3, 0,    5, 4, 0,    1, 5, 0,
      11, 6, 7,   11, 7, 8,   11, 8, 9,   11, 9,10,   11,10, 6,
       1, 2, 6,    2, 3, 7,    3, 4, 8,    4, 5, 9,    5, 1,10,
       2, 7, 6,    3, 8, 7,    4, 9, 8,    5,10, 9,    1, 6,10,
      };
   //  Vertex coordinates
   const float xyz[] =
      {
       0.000, 0.000, 1.000,
       0.894, 0.000, 0.447,
       0.276, 0.851, 0.447,
      -0.724, 0.526, 0.447,
      -0.724,-0.526, 0.447,
       0.276,-0.851, 0.447,
       0.724, 0.526,-0.447,
      -0.276, 0.851,-0.447,
      -0.894, 0.000,-0.447,
      -0.276,-0.851,-0.447,
       0.724,-0.526,-0.447,
       0.000, 0.000,-1.000
      };
   //  Vertex colors
   const float rgb[] =
      {
      0.0,0.0,1.0,
      0.0,1.0,0.0,
      0.0,1.0,1.0,
      1.0,0.0,0.0,
      1.0,0.0,1.0,
      1.0,1.0,0.0,
      0.0,0.0,1.0,
      0.0,1.0,0.0,
      0.0,1.0,1.0,
      1.0,0.0,0.0,
      1.0,0.0,1.0,
      1.0,1.0,0.0,
      };
   //  Define vertexes
   glVertexPointer(3,GL_FLOAT,0,xyz);
   glEnableClientState(GL_VERTEX_ARRAY);
   //  Define colors for each vertex
   glColorPointer(3,GL_FLOAT,0,rgb);
   glEnableClientState(GL_COLOR_ARRAY);
   //  Draw icosahedron
   glPushMatrix();
   glTranslatef(x,y,z);
   glRotatef(th,1,0,0);
   glScalef(s,s,s);
   glDrawElements(GL_TRIANGLES,N,GL_UNSIGNED_BYTE,index);
   glPopMatrix();
   //  Disable vertex array
   glDisableClientState(GL_VERTEX_ARRAY);
   //  Disable color array
   glDisableClientState(GL_COLOR_ARRAY);
}

/*
 * Icosahedron defined as triangles
 */
const int Ni=60;
//  Vertex coordinates and colors
const float xyzrgb[] =
{
    0.276, 0.851, 0.447,  0.0,0.0,1.0,
    0.894, 0.000, 0.447,  0.0,0.0,1.0,
    0.000, 0.000, 1.000,  0.0,0.0,1.0,
   -0.724, 0.526, 0.447,  0.0,1.0,0.0,
    0.276, 0.851, 0.447,  0.0,1.0,0.0,
    0.000, 0.000, 1.000,  0.0,1.0,0.0,
   -0.724,-0.526, 0.447,  0.0,1.0,1.0,
   -0.724, 0.526, 0.447,  0.0,1.0,1.0,
    0.000, 0.000, 1.000,  0.0,1.0,1.0,
    0.276,-0.851, 0.447,  1.0,0.0,1.0,
   -0.724,-0.526, 0.447,  1.0,0.0,1.0,
    0.000, 0.000, 1.000,  1.0,0.0,1.0,
    0.894, 0.000, 0.447,  1.0,1.0,0.0,
    0.276,-0.851, 0.447,  1.0,1.0,0.0,
    0.000, 0.000, 1.000,  1.0,1.0,0.0,
    0.000, 0.000,-1.000,  0.0,0.0,1.0,
    0.724, 0.526,-0.447,  0.0,0.0,1.0,
   -0.276, 0.851,-0.447,  0.0,0.0,1.0,
    0.000, 0.000,-1.000,  0.0,1.0,0.0,
   -0.276, 0.851,-0.447,  0.0,1.0,0.0,
   -0.894, 0.000,-0.447,  0.0,1.0,0.0,
    0.000, 0.000,-1.000,  0.0,1.0,1.0,
   -0.894, 0.000,-0.447,  0.0,1.0,1.0,
   -0.276,-0.851,-0.447,  0.0,1.0,1.0,
    0.000, 0.000,-1.000,  1.0,0.0,0.0,
   -0.276,-0.851,-0.447,  1.0,0.0,0.0,
    0.724,-0.526,-0.447,  1.0,0.0,0.0,
    0.000, 0.000,-1.000,  1.0,0.0,1.0,
    0.724,-0.526,-0.447,  1.0,0.0,1.0,
    0.724, 0.526,-0.447,  1.0,0.0,1.0,
    0.894, 0.000, 0.447,  1.0,1.0,0.0,
    0.276, 0.851, 0.447,  1.0,1.0,0.0,
    0.724, 0.526,-0.447,  1.0,1.0,0.0,
    0.276, 0.851, 0.447,  0.0,0.0,1.0,
   -0.724, 0.526, 0.447,  0.0,0.0,1.0,
   -0.276, 0.851,-0.447,  0.0,0.0,1.0,
   -0.724, 0.526, 0.447,  0.0,1.0,0.0,
   -0.724,-0.526, 0.447,  0.0,1.0,0.0,
   -0.894, 0.000,-0.447,  0.0,1.0,0.0,
   -0.724,-0.526, 0.447,  0.0,1.0,1.0,
    0.276,-0.851, 0.447,  0.0,1.0,1.0,
   -0.276,-0.851,-0.447,  0.0,1.0,1.0,
    0.276,-0.851, 0.447,  1.0,0.0,0.0,
    0.894, 0.000, 0.447,  1.0,0.0,0.0,
    0.724,-0.526,-0.447,  1.0,0.0,0.0,
    0.276, 0.851, 0.447,  1.0,0.0,1.0,
   -0.276, 0.851,-0.447,  1.0,0.0,1.0,
    0.724, 0.526,-0.447,  1.0,0.0,1.0,
   -0.724, 0.526, 0.447,  1.0,1.0,0.0,
   -0.894, 0.000,-0.447,  1.0,1.0,0.0,
   -0.276, 0.851,-0.447,  1.0,1.0,0.0,
   -0.724,-0.526, 0.447,  0.0,0.0,1.0,
   -0.276,-0.851,-0.447,  0.0,0.0,1.0,
   -0.894, 0.000,-0.447,  0.0,0.0,1.0,
    0.276,-0.851, 0.447,  0.0,1.0,0.0,
    0.724,-0.526,-0.447,  0.0,1.0,0.0,
   -0.276,-0.851,-0.447,  0.0,1.0,0.0,
    0.894, 0.000, 0.447,  0.0,1.0,1.0,
    0.724, 0.526,-0.447,  0.0,1.0,1.0,
    0.724,-0.526,-0.447,  0.0,1.0,1.0,
};

/*
 *  Draw icosahedron using client side arrays
 *     at (x,y,z)
 *     size  s
 *     rotated th about the x axis
 */
static void icosahedron2(float x,float y,float z,float s,float th)
{
   //  Define vertexes
   glVertexPointer(3,GL_FLOAT,6*sizeof(float),xyzrgb);
   glEnableClientState(GL_VERTEX_ARRAY);
   //  Define colors for each vertex
   glColorPointer(3,GL_FLOAT,6*sizeof(float),xyzrgb+3);
   glEnableClientState(GL_COLOR_ARRAY);
   //  Draw icosahedron
   glPushMatrix();
   glTranslatef(x,y,z);
   glRotatef(th,1,0,0);
   glScalef(s,s,s);
   glDrawArrays(GL_TRIANGLES,0,Ni);
   glPopMatrix();
   //  Disable vertex array
   glDisableClientState(GL_VERTEX_ARRAY);
   //  Disable color array
   glDisableClientState(GL_COLOR_ARRAY);
}

/*
 *  Draw icosahedron using VBO
 *     at (x,y,z)
 *     size  s
 *     rotated th about the x axis
 */
static unsigned int vbo3=0; //  Icosahedron VBO
static void icosahedron3(float x,float y,float z,float s,float th)
{
   //  Bind VBO
   if (vbo3)
      glBindBuffer(GL_ARRAY_BUFFER,vbo3);
   //  Initialize VBO on first call
   else
   {
      //  Get buffer name
      glGenBuffers(1, &vbo3);
      //  Bind VBO
      glBindBuffer(GL_ARRAY_BUFFER, vbo3);
      //  Copy icosahedron to VBO
      glBufferData(GL_ARRAY_BUFFER,sizeof(xyzrgb),xyzrgb,GL_STATIC_DRAW);
   }

   //  Define vertexes
   glVertexPointer(3,GL_FLOAT,6*sizeof(float),(void*)0);
   glEnableClientState(GL_VERTEX_ARRAY);
   //  Define colors for each vertex
   glColorPointer(3,GL_FLOAT,6*sizeof(float),(void*)12);
   glEnableClientState(GL_COLOR_ARRAY);
   //  Draw icosahedron
   glPushMatrix();
   glTranslatef(x,y,z);
   glRotatef(th,1,0,0);
   glScalef(s,s,s);
   glDrawArrays(GL_TRIANGLES,0,Ni);
   glPopMatrix();
   //  Disable vertex array
   glDisableClientState(GL_VERTEX_ARRAY);
   //  Disable color array
   glDisableClientState(GL_COLOR_ARRAY);
   //  Release VBO
   glBindBuffer(GL_ARRAY_BUFFER,0);
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
   //  Undo previous transformations
   glLoadIdentity();
   //  Set view angle
   glRotatef(ph,1,0,0);
   glRotatef(th,0,1,0);
   //  Decide what to draw
   switch (mode)
   {
      //  Draw cubes
      case 0:
         cube(0,0,0 , 0.3,0.3,0.3 , 0);
         cube(1,0,0 , 0.3,0.2,0.2 , 45);
         cube(0,1,0 , 0.4,0.4,0.2 , 90);
         break;
      //  Draw spheres
      case 1:
         sphere1(0,0,0 , 0.4);
         sphere1(1,0,0 , 0.2);
         sphere2(0,1,0 , 0.2);
         break;
      //  Line airplane
      case 2:
         FlatPlane(GL_LINE_LOOP , 0,0,0);
         break;
      //  Polygon airplane
      case 3:
         FlatPlane(GL_POLYGON , 0,0,0);
         break;
      // Three solid airplanes
      case 4:
         SolidPlane( 0, 0, 0 , 1,0,0 , 0, 1,0);
         SolidPlane(-1, 1, 0 ,-1,0,0 , 0,-1,0);
         SolidPlane(-1,-1, 0 ,-1,0,0 , 0, 1,0);
         break;
      // Icosahedron1
      case 5:
         icosahedron1(0,0,0,1.2,0);
         break;
      // Icosahedron2
      case 6:
         icosahedron2(0,0,0,1.2,0);
         break;
      // Icosahedron3
      case 7:
         icosahedron3(0,0,0,1.2,0);
         break;
      // Mix of objects
      case 8:
         //  Cube
         cube(-1,0,0 , 0.3,0.3,0.3 , 3*zh);
         //  Ball
         sphere1(0,0,0 , 0.3);
         //  Solid Airplane
         SolidPlane(Cos(zh),Sin(zh), 0 ,-Sin(zh),Cos(zh),0 , Cos(4*zh),0,Sin(4*zh));
         //  Icosahedron
         icosahedron3(1,0,0,0.5,zh);
         //  Utah Teapot
         glPushMatrix();
         glTranslatef(0,0,-1);
         glRotatef(zh,0,1,0);
         glColor3f(Cos(zh)*Cos(zh),0,Sin(zh)*Sin(zh));
         glutSolidTeapot(0.5);
         glPopMatrix();
         break;
   }
   //  White
   glColor3f(1,1,1);
   //  Draw axes
   if (axes)
   {
      const double len=1.5;  //  Length of axes
      glBegin(GL_LINES);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(len,0.0,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,len,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,0.0,len);
      glEnd();
      //  Label axes
      glRasterPos3d(len,0.0,0.0);
      Print("X");
      glRasterPos3d(0.0,len,0.0);
      Print("Y");
      glRasterPos3d(0.0,0.0,len);
      Print("Z");
   }
   //  Five pixels from the lower left corner of the window
   glWindowPos2i(5,5);
   //  Print the text string
   Print("Angle=%d,%d    %s",th,ph,text[mode]);
   //  Render the scene
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
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
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
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
   //  Switch display mode
   else if (ch == 'm')
      mode = (mode+1)%9;
   else if (ch == 'M')
      mode = (mode+8)%9;
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   //  Set the viewport to the entire window
   glViewport(0,0, RES*width,RES*height);
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  Orthogonal projection
   const double dim=2.5;
   double asp = (height>0) ? (double)width/height : 1;
   glOrtho(-asp*dim,+asp*dim, -dim,+dim, -dim,+dim);
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}

/*
 *  GLUT calls this routine when there is nothing else to do
 */
void idle()
{
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   zh = fmod(90*t,360);
   glutPostRedisplay();
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT and process user parameters
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitWindowSize(600,600);
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   //  Create the window
   glutCreateWindow("Objects");
#ifdef USEGLEW
   //  Initialize GLEW
   if (glewInit()!=GLEW_OK) Fatal("Error initializing GLEW\n");
#endif
   //  Tell GLUT to call "idle" when there is nothing else to do
   glutIdleFunc(idle);
   //  Tell GLUT to call "display" when the scene should be drawn
   glutDisplayFunc(display);
   //  Tell GLUT to call "reshape" when the window is resized
   glutReshapeFunc(reshape);
   //  Tell GLUT to call "special" when an arrow key is pressed
   glutSpecialFunc(special);
   //  Tell GLUT to call "key" when a key is pressed
   glutKeyboardFunc(key);
   //  Pass control to GLUT so it can interact with the user
   glutMainLoop();
   return 0;
}
