//
//  Light.cpp
//  OpenGL
//
//  Created by beom.93 on 2022/11/19.
//

#include "Light.hpp"


Light::Light(glm::vec3 color)
{
    this->color = color;
}


void Light::Initialize(Shader shader)
{
    shader.SetUniform3f("ambient_color", color.r, color.g, color.b);
}

