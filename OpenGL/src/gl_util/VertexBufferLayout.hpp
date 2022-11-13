//
//  VertexBufferLayout.hpp
//  OpenGL
//
//  Created by beom.93 on 2022/11/13.
//

#ifndef VertexBufferLayout_hpp
#define VertexBufferLayout_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include "VertexBufferElement.hpp"

class VertexBufferLayout {
private:
    //하나의 layout은 여러개의 element를 갖고 있음(ex, position, normal, color, etc...)
    std::vector<VertexBufferElement> m_Elements;
    //vertex하나당 데이터가 얼마나 떨어져있는지 stride를 멤버변수로 갖고 있음
    unsigned int m_Stride;
    
public:
    VertexBufferLayout() {
        this->m_Stride = 0;
    }
    
    template<typename T>
    void Push(unsigned int count)
    {
        
    }

    //template specializations
    template<>
    void Push<float>(unsigned int count)
    {
        m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT); //vertex 하나당 float 데이터가 count개 추가될수록, count * size(GL_FLOAT)씩 stride가 커져야 함
    }

    template<>
    void Push<unsigned int>(unsigned int count)
    {
        m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT); //위와 마찬가지
    }

    template<>
    void Push<unsigned char>(unsigned int count)
    {
        m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
    }

    inline const std::vector<VertexBufferElement>& GetElement() const { return m_Elements; }
    inline unsigned int GetStride() const { return m_Stride; }
};

#endif /* VertexBufferLayout_hpp */
