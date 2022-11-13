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

class IndexBuffer {
  
private :
    GLuint bufferId;
    unsigned int count;
    
public :
    IndexBuffer(unsigned int *arr, unsigned int count);
    ~IndexBuffer();
    void Bind() const;
    void Unbind() const;
    
    inline unsigned int GetCount() const {
        return count;
    }
};

#endif /* IndexBuffer_hpp */
