#version 450

layout(binding=0) uniform UniformBufferObject {
   mat4 model;  // Model matrix
   mat4 view;   // View matrix
   mat4 proj;   // Projection matrix
   mat4 norm;   // Normal matrix (passed as 4x4 to facilitate alignment)
   vec4 pos;    // Light position
   vec4 Ca;     // Light ambient
   vec4 Cd;     // Light diffuse
   vec4 Cs;     // Light specular
   vec4 Ks;     // Material specular
   float Ns;    // Material shininess
   } ubo;

layout(location=0) in  vec3 xyz;   //  Vertex
layout(location=1) in  vec3 nml;   //  Normal
layout(location=2) in  vec3 rgb;   //  Color
layout(location=3) in  vec2 st;    //  Texture

layout(location=0) out vec3 Norm;  // Normal vector
layout(location=1) out vec3 Light; // Light vector
layout(location=2) out vec3 View;  // Eye vector
layout(location=3) out vec3 col;   // Color
layout(location=4) out vec2 t2d;   // Texture

void main()
{
   //  Vertex position
   vec4 P4 = ubo.view*ubo.model*vec4(xyz,1.0);
   vec3 P = P4.xyz/P4.w;
   //  Normal vector
   Norm = mat3(ubo.norm)*nml;
   //  Light vector
   vec4 L4 = ubo.view*ubo.pos;
   Light = L4.xyz/L4.w - P;
   //  Eye vector
   View = -P;
   //  Color and texture coordinates
   col = rgb;
   t2d = st;
   //  Vertex projection
   gl_Position = ubo.proj*P4;
}
