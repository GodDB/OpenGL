//
//  DataBuffer.hpp
//  OpenGL
//
//  Created by beom.93 on 2022/11/11.
//

#ifndef DataBuffer_hpp
#define DataBuffer_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


class DataBuffer {
public :
    DataBuffer(GLfloat *data, int size);
    ~DataBuffer();
    
private:
    GLuint bufferId;
};

#endif /* DataBuffer_hpp */
