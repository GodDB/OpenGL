//
//  IndexBuffer.hpp
//  OpenGL
//
//  Created by beom.93 on 2022/11/11.
//

#ifndef IndexBuffer_hpp
#define IndexBuffer_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class IndexBuffer {
  
private :
    GLuint bufferId;
    
public :
    IndexBuffer(unsigned int *arr, int size);
    ~IndexBuffer();
    void bind();
    void unbind();
};

#endif /* IndexBuffer_hpp */
