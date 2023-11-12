//  Identity vertex shader
#version 120

void main()
{
   //  Use color unchanged
   gl_FrontColor = gl_Color;
   //  Set vertex coordinates
   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
