// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
#include "common/shader.hpp"
#include "DataBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
GLFWwindow* window;

int main( void )
{
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow( 1024, 768, "Tutorial 02 - Red triangle", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }


    GLfloat g_vertex_buffer_data[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // pos, color
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f
    };
    
    // 사각형을 그리려면 2개의 삼각형이 필요하고, 그에 대응되는 버텍스 어레이의 인덱스를 정의
    unsigned int indices[] {
        0, 1, 2,
        2, 3, 0
    };
    
    // 데이터를 전달하는 과정
    // 1. vertex array 생성
    VertexArray vertaxArr;
    
    // 2. vertex buffer 생성
    DataBuffer dataBuffer { g_vertex_buffer_data, 6 * 4 };

    IndexBuffer indexBuffer { indices, 3 * 2 };
    
    // 데이터를 해석하는 방법 전달
    vertaxArr.defineAttribute(
                              0,
                              3,
                              GL_FLOAT,
                              GL_FALSE,
                              sizeof(float) * 6,
                              (void*)0
                              );

    vertaxArr.defineAttribute(
                              1,
                              3,
                              GL_FLOAT,
                              GL_FALSE,
                              sizeof(float) * 6,
                              (void*) (sizeof(float) * 3)
                              );
    
    
    // vertex, fragment shader 생성
    GLuint programID = LoadShaders(
                                   "res/shaders/SimpleVertexShader.vertexshader",
                                   "res/shaders/SimpleFragmentShader.fragmentshader" );
    
    // Use our shader
    glUseProgram(programID);
    
    // fragment shader에 정의된 u_Color 포인터를 가져온다
    GLuint uColorPtr = glGetUniformLocation(programID, "u_Color");
    // u_Color라는 유니폼 변수에 값을 세팅한다.
    glUniform4f(uColorPtr, 0.3f, 0.3f, 0.8f, 1.0f);
    
    glBindVertexArray(0);
    /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            vertaxArr.activate(); // 버텍스 어레이 액티브 상태로 전환
            glDrawElements(
                           GL_TRIANGLES, // 그리고자 하는 것
                           6, // 인덱스 갯수
                           GL_UNSIGNED_INT, // 인덱스 데이터 타입
                           nullptr // ㅑㄹ
                           );
            
            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

    // Cleanup VBO

    glDeleteProgram(programID);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}

