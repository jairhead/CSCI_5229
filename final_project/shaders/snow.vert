// Snowflake vertex shader
#version 400 core

// Inputs
in vec2 vertTexture;

// Outputs
out vec2 geomTexture;

// Main
void main() {
  geomTexture = vertTexture;
}
