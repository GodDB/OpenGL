// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
#include "common/shader.hpp"
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

    glfwWindowHint(GLFW_SAMPLES, 4);
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

    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         0.0f,  1.0f, 0.0f,
    };
    
    // 데이터를 전달하는 과정
    // 1. vertex array 생성
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID); // 1. 버텍스 어레이 생성 생성
    glBindVertexArray(VertexArrayID); // 버텍스 어레이 액티브 상태로 전환
    
    // 2. vertex buffer 생성
    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer); // 1. 버퍼 생성
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer); // 2. 버퍼 액티브 상태로 전환
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW); // 버퍼에 데이터 전달


    // vertex, fragment shader 생성
    GLuint programID = LoadShaders(
                                   "res/shaders/SimpleVertexShader.vertexshader",
                                   "res/shaders/SimpleFragmentShader.fragmentshader" );



    // 버텍스 어레이 활성
    glEnableVertexAttribArray(0);
    // 버텍스 버퍼 활성화
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );
    
    // Use our shader
    glUseProgram(programID);
    
    /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            glDrawArrays(GL_TRIANGLES, 0, 3); //Draw call
            
            //이번에는 빨간색 삼각형이 나와야 함!

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

    // Cleanup VBO
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteProgram(programID);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}

