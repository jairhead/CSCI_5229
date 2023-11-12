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

layout(binding = 1) uniform sampler2D tex; // Texture sampler

layout(location=0) in vec3 Norm;  // Normal vector
layout(location=1) in vec3 Light; // Light vector
layout(location=2) in vec3 View;  // Eye vector
layout(location=3) in vec3 col;   // Color
layout(location=4) in vec2 t2d;   // Texture

layout(location=0) out vec4 fragColor; // Pixel color

void main()
{
   //  Normalize vectors and calculate reflection
   vec3 N = normalize(Norm);
   vec3 L = normalize(Light);
   vec3 V = normalize(View);
   vec3 R = reflect(-L,N);
   //  Diffuse light is cosine of light and normal vectors
   float Id = max(dot(L,N) , 0.0);
   //  Specular is cosine of reflected and view vectors
   float Is = (Id>0.0) ? pow(max(dot(R,V),0.0) , ubo.Ns) : 0.0;

   //  Sum color types
   vec4 Kd = vec4(col,1);
   vec4 color = Kd*ubo.Ca + Id*Kd*ubo.Cd + Is*ubo.Ks*ubo.Cs;

   //  Modulate color by texture
   fragColor = color * texture(tex,t2d);
}
