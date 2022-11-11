//
//  DataBuffer.cpp
//  OpenGL
//
//  Created by beom.93 on 2022/11/11.
//

#include "DataBuffer.hpp"


DataBuffer::DataBuffer(GLfloat *data, int size) {
    // 2. vertex buffer 생성
    glGenBuffers(1, &bufferId); // 1. 버퍼 생성
    glBindBuffer(GL_ARRAY_BUFFER, bufferId); // 2. 버퍼 액티브 상태로 전환
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW); // 버퍼에 데이터 전달

}

DataBuffer::~DataBuffer() {
    glDeleteBuffers(1, &bufferId);
}


