//
//  Shader.cpp
//  OpenGL
//
//  Created by beom.93 on 2022/11/11.
//

#include "Shader.hpp"

Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader)
    : m_RendererID{ 0 }
{
    ShaderProgramSource source = ParseShader(vertexShader, fragmentShader);

    m_RendererID = CreateShader(source.VertexSource, source.FragSource);
}

Shader::~Shader()
{
    glDeleteProgram(m_RendererID);
}

ShaderProgramSource Shader::ParseShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertexShader, std::ios::in);
    if(VertexShaderStream.is_open()){
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    } else {
        std::cout << "버텍스 쉐이더 파일 못 읽음" << std::endl;
    }

    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragmentShader, std::ios::in);
    if(FragmentShaderStream.is_open()){
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        FragmentShaderCode = sstr.str();
        FragmentShaderStream.close();
    }

    return { VertexShaderCode, FragmentShaderCode };
}


unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type); //셰이더 객체 생성(마찬가지)
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr); // 셰이더의 소스 코드 명시
    glCompileShader(id); // id에 해당하는 셰이더 컴파일

    // Error Handling(없으면 셰이더 프로그래밍할때 괴롭다...)
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result); //셰이더 프로그램으로부터 컴파일 결과(log)를 얻어옴
    if (result == GL_FALSE) //컴파일에 실패한 경우
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length); //log의 길이를 얻어옴
        char* message = (char*)alloca(length * sizeof(char)); //stack에 동적할당
        glGetShaderInfoLog(id, length, &length, message); //길이만큼 log를 얻어옴
        std::cout << "셰이더 컴파일 실패! " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id); //컴파일 실패한 경우 셰이더 삭제
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragShader)
{
    unsigned int program = glCreateProgram(); //셰이더 프로그램 객체 생성(int에 저장되는 것은 id)
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragShader);

    //컴파일된 셰이더 코드를 program에 추가하고 링크
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    //셰이더 프로그램을 생성했으므로 vs, fs 개별 프로그램은 더이상 필요 없음
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void Shader::Bind() const
{
    glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    glUniform4f(GetUniformLocation(name),v0, v1, v2, v3);
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
    glUniform3f(GetUniformLocation(name), v0, v1, v2);
}

void Shader::SetUniform1f(const std::string& name, float value)
{
    glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform1i(const std::string& name, int value)
{
    glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& mat) {
    glUniformMatrix4fv(
                 GetUniformLocation(name),
                 1, //전달할 행렬 갯수
                 GL_FALSE,
                 &mat[0][0] // 배열 첫번째 포인터 전달
                 );
}

int Shader::GetUniformLocation(const std::string& name)
{
    //반복해서 uniform을 찾지 않고 map에 저장해둠
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    int location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location == -1)
    {
        std::cout << "Warning: unform '" << name << "' doesn't exist!\n";
    }

    m_UniformLocationCache[name] = location;

    return location;
}
