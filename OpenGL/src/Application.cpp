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
#include "Model.hpp"
#include "Renderer.hpp"
#include "Light.hpp"

// homebrew에서 받은 외부 라이브러리 저장 방법 

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
 
    // -- model import
    Model model;
    model.loadModel("/Users/beom.93/open_gl/c/OpenGL/OpenGL/res/model/teapot.obj");
    
    // -- 카메라 생성
    //yaw 값이 0일때는 front가 [1,0,0]이므로, yaw를 90으로 해서 초기 front가 [0,0,-1]이 되도록 함
    Camera camera{
        glm::vec3{0.0f,0.0f,30.0f},
        glm::vec3{0.0f,1.0f,0.0f},
        -90.0f,
        0.0f,
        5.0f,
        0.5f
    };
        
    // -- transform 정의
    // 가라
    glm::mat4 t_model = getTranslationTransform(0.0f, 0.0f, 0.0f);
    glm::mat4 t_proj = glm::perspective(
                                      45.0f,
                                      (float)(window.GetBufferWidth() / window.GetBufferHeight()),
                                      0.1f,
                                      100.0f);
    
    // -- shader 생성
    // vertex, fragment shader 생성
    Shader shader {
        "res/shaders/SimpleVertexShader.vertexshader",
        "res/shaders/SimpleFragmentShader.fragmentshader"
    };
    shader.Bind();
    shader.SetUniformMat4f("transform_model", t_model);
    shader.SetUniformMat4f("transform_view", camera.calculateViewMatrix());
    shader.SetUniformMat4f("transform_proj", t_proj);
    
    Light light {
        glm::vec3 { 0.3f, 0.3f, 0.3f },
        glm::vec3 { 0.7f, -0.3f, -0.7f }
    };
    light.Initialize(shader);
                 
    //--------------Texture 생성---------//
    Texture texture{ "/Users/beom.93/open_gl/c/OpenGL/OpenGL/res/texture/uvchecker.jpg" };
    texture.Bind(); //0번 슬롯에 바인딩
    shader.SetUniform1i("u_Texture", 0); //0번 슬롯의 텍스처를 사용할 것이라는 것을 셰이더에 명시

  
    /* Loop until the user closes the window */
    //매 프레임마다 소요되는 시간을 계산/저장 하기 위한 변수
    float deltaTime = 0.0f;
    float lastTime = 0.0f;
    
    while (!window.GetShouldClose())
    {
          
        float now = glfwGetTime(); //현재 시간
        deltaTime = now - lastTime; //소요 시간 = 현재 시간 - 이전 프레임 시간
        lastTime = now;

        //poll event 부분은 유저 입력에 필요하므로 남겨둠
        glfwPollEvents();

        camera.KeyControl(window.GetKeys(), deltaTime);
        camera.MouseControl(window.GetXChange(), window.GetYChange());

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        shader.Bind();
        shader.SetUniformMat4f("transform_model", t_model);
        shader.SetUniformMat4f("transform_view", camera.calculateViewMatrix());
        shader.SetUniformMat4f("transform_proj", t_proj);
        glm::vec3 camera_eye = camera.GetEye();
        shader.SetUniform3f("u_camera_pos", camera_eye.x, camera_eye.y, camera_eye.z);
        model.RenderModel(shader);
            
        /* Swap front and back buffers */
        window.SwapBuffers();
    }
    return 0;
}

