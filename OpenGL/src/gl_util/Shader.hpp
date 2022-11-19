//
//  Shader.hpp
//  OpenGL
//
//  Created by beom.93 on 2022/11/11.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include "glm.hpp"
#include <GL/glew.h>

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragSource;
};


class Shader
{
private:
    unsigned int m_RendererID;
    std::unordered_map<std::string, int> m_UniformLocationCache;
public:
    Shader(const std::string& vertexShader, const std::string& fragmentShader);
    ~Shader();

    void Bind() const; //함수는 glUseProgram()이지만, 앞서 설명한 것과 같이 바인딩("작업 상태로 만듬")과 같은 역할이기 때문에 Bind()로 통일
    void Unbind() const;

    //Set Uniforms
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    void SetUniform3f(const std::string& name, float v0, float v1, float v2);
    void SetUniform1f(const std::string& name, float value);
    void SetUniform1i(const std::string& name, int value); //shader slot을 명시하
    void SetUniformMat4f(const std::string& name, const glm::mat4& mat);
private:
    ShaderProgramSource ParseShader(const std::string& vertexShader, const std::string& fragmentShader);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragShader);

    int GetUniformLocation(const std::string& name);
};

#endif /* Shader_hpp */
