#version 330 core

in vec3 f_color;
in vec2 f_texCoord;

// Ouput data
out vec4 color;

uniform sampler2D outTexture;

void main()
{

    // Output color = red
    //color = f_color;
    color = texture(outTexture, f_texCoord);

}
