//
//  VertexArray.hpp
//  OpenGL
//
//  Created by beom.93 on 2022/11/11.
//

#ifndef VertexArray_hpp
#define VertexArray_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class VertexArray {
    
private :
    GLuint id;
    
public :
    VertexArray();
    ~VertexArray();
    void activate();
    void defineAttribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
};

#endif /* VertexArray_hpp */
