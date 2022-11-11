//
//  VertexArray.cpp
//  OpenGL
//
//  Created by beom.93 on 2022/11/11.
//

#include "VertexArray.hpp"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &id); // 1. 버텍스 어레이 생성 생성
    activate(); // 버텍스 어레이 액티브 상태로 전환
}

VertexArray::~VertexArray(){
    glDeleteVertexArrays(1, &id);
}

void VertexArray::activate(){
    glBindVertexArray(id);
}

void VertexArray::defineAttribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) {
    //attribute를 활성화(enable)
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(
                          index,  //몇번째 index attribute인가?
                          size, // size
                          type, // type
                          normalized, // normalized
                          stride, // stride
                          pointer //  array buffer offset
                          );
}
