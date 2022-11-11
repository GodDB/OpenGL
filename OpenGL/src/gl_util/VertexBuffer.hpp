//
//  DataBuffer.hpp
//  OpenGL
//
//  Created by beom.93 on 2022/11/11.
//

#ifndef VertexBuffer_hpp
#define VertexBuffer_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


class VertexBuffer {
public :
    VertexBuffer(GLfloat *data, int size);
    ~VertexBuffer();
    void bind();
    void unbind();
    
private:
    GLuint bufferId;
};

#endif /* DataBuffer_hpp */
