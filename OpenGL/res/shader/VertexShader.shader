#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 texCoord;

uniform mat4 world_tramsform_mat;
uniform mat4 view_transform_mat;
uniform mat4 perspective_transform_mat;

out vec2 f_texCoord;

void main()
{
    gl_Position = perspective_transform_mat * view_transform_mat * world_tramsform_mat * vec4(pos, 1.0);
    f_texCoord = texCoord;
}

