//
//  IndexBuffer.cpp
//  OpenGL
//
//  Created by beom.93 on 2022/11/11.
//

#include "IndexBuffer.hpp"

IndexBuffer::IndexBuffer(unsigned int *arr, unsigned int count) {
    this->count = count;
    glGenBuffers(1, &bufferId); // 인덱스를 받을 버퍼 생성
    Bind(); // 버퍼 엑티브 생태로 전환
    glBufferData(
                 GL_ELEMENT_ARRAY_BUFFER,
                 count * sizeof(unsigned int),
                 arr,
                 GL_STATIC_DRAW
                 ); // 버퍼에 데이터 전달
    
}
IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &bufferId);
}

void IndexBuffer::Bind() const{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
}
void IndexBuffer::Unbind() const{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); 
}
