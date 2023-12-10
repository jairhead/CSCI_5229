// Snowflake geometry shader
#version 400 core

// Convert
layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

// Projection & model view matrices
uniform mat4 ProjectionMatrix;
uniform mat4 ModelViewMatrix;

// Attributes
in vec2 geomTexture[1];
out vec2 fragTexture;

// Dimensions of snow flake (world & texture)
uniform float wX;
uniform float wY;
uniform float tX;
uniform float tY;

// Billboard function
void billboardFunc(float x, float y, float tX, float tY) {
  // Add texture coordinates to world coordinates
  fragTexture = geomTexture[0] + vec2(tX, tY);

  // Calculate the position
  vec2 delta = vec2(x, y);
  vec4 position = vec4(0, 0, 0, 1);
  position.x = position.x + dot(delta, ModelViewMatrix[0].xy);
  position.y = position.y + dot(delta, ModelViewMatrix[1].xy);
  position.z = position.z + dot(delta, ModelViewMatrix[2].xy);

  // Set the position and emit
  gl_Position = ProjectionMatrix * ModelViewMatrix * position;
  EmitVertex();
}

// Main
void main() {
  billboardFunc(0, 0, 0, 0);
  billboardFunc(wX, 0, wY, 0);
  billboardFunc(0, wY, 0, tY);
  billboardFunc(wX, wY, tX, tY);
  EndPrimitive();
}
