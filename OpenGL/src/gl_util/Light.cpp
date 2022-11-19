//
//  Light.cpp
//  OpenGL
//
//  Created by beom.93 on 2022/11/19.
//

#include "Light.hpp"


Light::Light(glm::vec3 color, glm::vec3 diffuseDirection)
{
    this->color = color;
    this->diffuseDirection = diffuseDirection;
}


void Light::Initialize(Shader shader)
{
    shader.SetUniform3f("ambient_color", color.r, color.g, color.b);
    shader.SetUniform3f("diffuse_direction", diffuseDirection.x, diffuseDirection.y, diffuseDirection.z);
}

