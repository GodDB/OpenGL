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

static glm::mat4 getScaleTransform(float scaleX, float scaleY, float scaleZ);

static glm::mat4 getRotationXTransform(double rotateX);

static glm::mat4 getRotationYTransform(double rotateY);

static glm::mat4 getRotationZTransform(double rotateZ);

static glm::mat4 getTranslationTransform(float t_x, float t_y, float t_z);


#endif /* TransformUtil_hpp */
