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
#include "VertexBufferLayout.hpp"
#include "VertexBufferElement.hpp"
#include "VertexBuffer.hpp"

class VertexArray {
    
private :
    GLuint id;
    
public :
    VertexArray();
    ~VertexArray();
    void Bind() const;
    void Unbind() const;
    
    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
};

#endif /* VertexArray_hpp */
