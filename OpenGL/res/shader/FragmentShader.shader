#version 330 core

in vec2 f_texCoord;

// Ouput data
out vec4 color;

uniform sampler2D outTexture;

void main()
{
    color = texture(outTexture, f_texCoord);

}
