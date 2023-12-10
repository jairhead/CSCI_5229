// Snowflake fragment shader
#version 400 core

// Texture coordinates
in vec2 fragTexture;

// Input color
uniform vec4 inColor;

// Snowflake texture
uniform sampler2D snow;

// Final color for fragment
layout (location = 0) out vec4 FragColor;

void main()
{
  // Set the color
  vec4 outColor = inColor * texture(snow, fragTexture);

  // If the color is black, don't pass it through
  if (outColor.r + outColor.g + outColor.b < 0.1) {
    discard;
  }
  else {
    FragColor = texture(snow, fragTexture);
  }
}
