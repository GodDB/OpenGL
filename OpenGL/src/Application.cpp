// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <thread>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "glm.hpp"
#include "transform.hpp"
#include "TransformUtil.hpp"
#include "Window.hpp"
#include "Camera.hpp"


int main( void )
{
    Window window;
    window.Initialize();

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }

    GLfloat g_vertex_buffer_data[] = {
        -0.5f, -0.5f, -5.0f,
        0.5f, -0.5f, -5.0f,
        0.5f, 0.5f, -5.0f,
        -0.5f, 0.5f, -5.0f
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
    VertexBuffer dataBuffer { g_vertex_buffer_data, sizeof(g_vertex_buffer_data) };

    IndexBuffer indexBuffer { indices, sizeof(indices) };
    
    unsigned int spride = sizeof(float) * 3;
    // 데이터를 해석하는 방법 전달
    vertaxArr.defineAttribute(
                              0,
                              3,
                              GL_FLOAT,
                              GL_FALSE,
                              spride,
                              (void*)0
                              );

    // vertex, fragment shader 생성
    Shader shader {
        "res/shaders/SimpleVertexShader.vertexshader",
        "res/shaders/SimpleFragmentShader.fragmentshader"};
    
    //yaw 값이 0일때는 front가 [1,0,0]이므로, yaw를 90으로 해서 초기 front가 [0,0,-1]이 되도록 함
    Camera camera{
        glm::vec3{0.0f,0.0f,5.0f},
        glm::vec3{0.0f,1.0f,0.0f},
        -90.0f,
        0.0f,
        5.0f,
        0.5f
    };

    // 가라
    glm::mat4 model = getTranslationTransform(0.0f, 0.0f, 0.0f);
    glm::mat4 proj = getProjectionTransform(
                                            glm::radians(90.0f),
                                            window.GetBufferWidth() / window.GetBufferHeight(),
                                            1.0f,
                                            100.0f
                                            );
  
    /* Loop until the user closes the window */
    //매 프레임마다 소요되는 시간을 계산/저장 하기 위한 변수
        float deltaTime = 0.0f;
        float lastTime = 0.0f;
    
        while (!window.GetShouldClose())
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);
            
            float now = glfwGetTime(); //현재 시간
            deltaTime = now - lastTime; //소요 시간 = 현재 시간 - 이전 프레임 시간
            lastTime = now;

            //poll event 부분은 유저 입력에 필요하므로 남겨둠
            glfwPollEvents();

            camera.KeyControl(window.GetKeys(), deltaTime);
            camera.MouseControl(window.GetXChange(), window.GetYChange());

            vertaxArr.activate(); // 버텍스 어레이 액티브 상태로 전환
            shader.Bind();
            shader.SetUniformMat4f("transform_model", model);
            shader.SetUniformMat4f("transform_proj", proj);
            shader.SetUniformMat4f("transform_view", camera.calculateViewMatrix());
            
            glDrawElements(
                           GL_TRIANGLES, // 그리고자 하는 것
                           6, // 인덱스 갯수
                           GL_UNSIGNED_INT, // 인덱스 데이터 타입
                           nullptr // ㅑㄹ
                           );
            
            /* Swap front and back buffers */
            window.SwapBuffers();
        }
    return 0;
}

