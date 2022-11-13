//
//  TransformUtil.hpp
//  OpenGL
//
//  Created by beom.93 on 2022/11/12.
//

#ifndef TransformUtil_hpp
#define TransformUtil_hpp

#include <stdio.h>
#include "glm.hpp"


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
       0.0f, glm::cos(x_radians), -glm::sin(x_radians), 0.0f,
       0.0f, glm::sin(x_radians), glm::cos(x_radians), 0.0f,
       0.0f, 0.0f, 0.0f, 1.0f
   };
   return glm::transpose(R);
}

static glm::mat4 getRotationYTransform(double rotateY) {
   double y_radians = glm::radians(rotateY);
   
   glm::mat4 R = {
       glm::cos(y_radians), 0.0f, glm::sin(y_radians), 0.0f,
       0.0f, 1.0f, 0.0f, 0.0f,
       -glm::sin(y_radians), 0.0f, glm::cos(y_radians), 0.0f,
       0.0f, 0.0f, 0.0f, 1.0f
   };
   return glm::transpose(R);
}

static glm::mat4 getRotationZTransform(double rotateZ) {
   double z_radians = glm::radians(rotateZ);
   
   glm::mat4 R = {
       glm::cos(z_radians), -glm::sin(z_radians), 0.0f, 0.0f,
       glm::sin(z_radians), glm::cos(z_radians), 0.0f, 0.0f,
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

static glm::mat4 getProjectionTransform(float fovy, float aspect, float near, float far) {
    
    glm::mat4 P = {
        1/glm::tan(fovy/2), 0.0f, 0.0f, 0.0f,
        0.0f, 1/glm::tan(fovy/2), 0.0f, 0.0f,
        0.0f, 0.0f, -(far+near) / (far-near), -(2 * near * far) / (far - near),
        0.0f, 0.0f, -1.0f, 0.0f
    };
    
    return glm::transpose(P);
}

static float getDistance(glm::vec3 vec) {
    float base = (vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z);
    return std::sqrt(base);
}

static glm::vec3 normalize(glm::vec3 vec) {
    float distance = getDistance(vec);
    return vec / distance;
}

static glm::mat4 getViewTransform(glm::vec3 eye, glm::vec3 at, glm::vec3 up) {
    glm::vec3 vector_n = (eye - at) / getDistance(eye - at);
    glm::vec3 vector_u = glm::cross(up, vector_n) / getDistance(glm::cross(up, vector_n));
    glm::vec3 vector_v = glm::cross(vector_n, vector_u);

    glm::mat4 T = getTranslationTransform(-eye.x, -eye.y, -eye.z);
    glm::mat4 _R = glm::mat4 {
        vector_u.x, vector_u.y, vector_u.z, 0.0f,
        vector_v.x, vector_v.y, vector_v.z, 0.0f,
        vector_n.x, vector_n.y, vector_n.z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    glm::mat4 R = glm::transpose(_R);
    return R * T;
}


#endif /* TransformUtil_hpp */
