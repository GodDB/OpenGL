//
//  VertexBufferElement.hpp
//  OpenGL
//
//  Created by beom.93 on 2022/11/13.
//

#ifndef VertexBufferElement_hpp
#define VertexBufferElement_hpp

#include <stdio.h>
//Layout별로, 데이터를 어떻게 읽어와야 하는지에 대한 정보를 가지고있는 구조체
struct VertexBufferElement {
    
    unsigned int type;  // 데이터 타입
    unsigned int count; // 총 데이터 갯수
    unsigned int normalized; // 노말라이즈가 필요한지
    
    //타입별로 적절한 메모리 사이즈를 반환하는 static 함수
    static unsigned int GetSizeOfType(unsigned int type) {
        switch (type) {
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }
        std::cout << "잘못된 타입" << std::endl;
        return 0;
    }
};
#endif /* VertexBufferElement_hpp */
