//
//  IndexBuffer.cpp
//  OpenGL
//
//  Created by beom.93 on 2022/11/11.
//

#include "IndexBuffer.hpp"

IndexBuffer::IndexBuffer(unsigned int *arr, int size) {

    glGenBuffers(1, &bufferId); // 인덱스를 받을 버퍼 생성
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId); // 버퍼 엑티브 생태로 전환
    glBufferData(
                 GL_ELEMENT_ARRAY_BUFFER,
                 size,
                 arr,
                 GL_STATIC_DRAW
                 ); // 버퍼에 데이터 전달
    
}
IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &bufferId);
}

