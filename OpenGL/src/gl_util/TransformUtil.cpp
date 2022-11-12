//
//  TransformUtil.cpp
//  OpenGL
//
//  Created by beom.93 on 2022/11/12.
//

#include "TransformUtil.hpp"


#include <stdio.h>

static glm::mat4 getScaleTransform(float scaleX, float scaleY, float scaleZ) {
    glm::mat4 S = {
        scaleX, 0.0f, 0.0f, 0.0f,
        0.0f, scaleY, 0.0f, 0.0f,
        0.0f, 0.0f, scaleZ, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    return glm::transpose(S);
}

static glm::mat4 getRotationXTransform(double rotateX) {
    double x_radians = glm::radians(rotateX);
    
    glm::mat4 R = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, cos(x_radians), -sin(x_radians), 0.0f,
        0.0f, sin(x_radians), cos(x_radians), 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    return glm::transpose(R);
}

static glm::mat4 getRotationYTransform(double rotateY) {
    double y_radians = glm::radians(rotateY);
    
    glm::mat4 R = {
       cos(y_radians), 0.0f, sin(y_radians), 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        -sin(y_radians), 0.0f, cos(y_radians), 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    return glm::transpose(R);
}

static glm::mat4 getRotationZTransform(double rotateZ) {
    double z_radians = glm::radians(rotateZ);
    
    glm::mat4 R = {
        cos(z_radians), -sin(z_radians), 0.0f, 0.0f,
        sin(z_radians), cos(z_radians), 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    
    return glm::transpose(R);
}

static glm::mat4 getTranslationTransform(float t_x, float t_y, float t_z) {
    glm::mat4 T = {
      1.0f, 0.0f, 0.0f, t_x,
        0.0f, 1.0f, 0.0f, t_y,
        0.0f, 0.0f, 1.0f, t_z,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    
    return glm::transpose(T);
}
