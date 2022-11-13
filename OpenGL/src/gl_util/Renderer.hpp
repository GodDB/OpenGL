//
//  Renderer.hpp
//  OpenGL
//
//  Created by beom.93 on 2022/11/11.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <stdio.h>
#include <iostream>
#include <GL/glew.h>
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"

class Renderer {
public:
    //화면에 무언가를 그리위해서는 Vertex Array (Vertex Buffer는 여기에 포함되어 있음), Index Array, Shader Program이 필요함
    void Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader);
    void Clear() const;
};

#endif /* Renderer_hpp */
