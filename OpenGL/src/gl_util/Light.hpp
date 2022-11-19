//
//  Light.hpp
//  OpenGL
//
//  Created by beom.93 on 2022/11/19.
//

#ifndef Light_hpp
#define Light_hpp

#include <stdio.h>
#include <GL/glew.h>
#include "glm.hpp"
#include "Shader.hpp"

class Light {
public:
    Light()
    {
        
    }
    Light(glm::vec3 color);
    void Initialize(Shader shader);
private:
    glm::vec3 color;
};

#endif /* Light_hpp */
