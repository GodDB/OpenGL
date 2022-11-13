//
//  Renderer.cpp
//  OpenGL
//
//  Created by beom.93 on 2022/11/11.
//

#include "Renderer.hpp"

#include <iostream>

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
{
    //그리기 전에 무엇을 그릴지 바인딩
    shader.Bind();
    va.Bind();
    ib.Bind();

    //그리기
    glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
