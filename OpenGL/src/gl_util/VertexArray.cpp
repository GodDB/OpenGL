//
//  VertexArray.cpp
//  OpenGL
//
//  Created by beom.93 on 2022/11/11.
//

#include "VertexArray.hpp"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &id); // 1. 버텍스 어레이 생성 생성
    Bind(); // 버텍스 어레이 액티브 상태로 전환
}

VertexArray::~VertexArray(){
    glDeleteVertexArrays(1, &id);
}

void VertexArray::Bind() const {
    glBindVertexArray(id);
}
void VertexArray::Unbind() const {
    glBindVertexArray(0);
}
void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
    
    this->Bind(); //vao를 바인딩

    vb.Bind(); //Vertex Buffer를 바인딩
    
    const auto& elements = layout.GetElement();
    unsigned int offset = 0;
    for (int i=0;i<elements.size();i++)
    {
        const auto& element = elements[i];
        glEnableVertexAttribArray(i); //기존에는 0번만 존재했으나, position/normal/color등 여러 attribute가 생기면, 여러 attribute를 enable해야함
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset); //layout별로 데이터를 어떻게 읽어와야하는지를 element구조체로 가지고 있을 예정. 이를 활용함.
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
}
