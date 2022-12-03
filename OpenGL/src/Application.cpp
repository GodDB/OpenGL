//
//  Application.cpp
//  OpenGL
//
//  Created by beom.93 on 2022/12/03.
//

#include <iostream>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <vector>
#include "glm.hpp"
#include "matrix_transform.hpp"

#include "Shader.hpp"


static GLFWwindow* initializeWindow() {
    glfwInit();
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    glViewport(0, 0, 800, 600);
    glfwSwapInterval(1); //1이면 vsync rate와 같은 속도로 화면 갱신
    return window;
}

static void initGLEW()
{
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error\n";
    }
}

static std::vector<unsigned int> initModel()
{
    std::vector<unsigned int> vaos;
    for(int i = 0; i < 10; i++)
    {
    
        float vertices[] = {
            // positions          // colors           // 텍스처 인덱스
             0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
             0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
        };
        
        unsigned int indices[] = {  // note that we start from 0!
            1, 2, 3  // second triangle
        };
        
        unsigned int VBO, VAO, EBO;
        // vao 버퍼 생성
        glGenVertexArrays(1, &VAO);
        // vbo 버퍼 생성
        glGenBuffers(1, &VBO);
        // ebo(index buffer) 생성
        glGenBuffers(1, &EBO);

        // vao 버퍼 바인드
        glBindVertexArray(VAO);
        
        // vbo 버퍼 바인드 및 데이터 전달
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
        // ebo 버퍼 바인드 및 데이터 전달
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        
        // 데이터를 어떻게 해석할 것인가? (position)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(0 * sizeof(float)));
        glEnableVertexAttribArray(0);
        
        // 데이터를 어떻게 해석할 것인가? (color)
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        
        // 데이터를 어떻게 해석할 것인가? (텍스처 인덱스)
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        vaos.push_back(VAO);
    }
    return vaos;
}

// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;

// camera
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = static_cast<float>(2.5 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraFront * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraFront * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}


int main()
{
    GLFWwindow* window = initializeWindow();
    initGLEW();
    
    Shader shader { "./res/shader/VertexShader.shader", "./res/shader/FragmentShader.shader" };
    shader.Bind();
    
    // 텍스처 mipmap 정의 - 텍스처 인덱스가 넘어갔을 때 텍스처를 어떻게 표현할 것인가? - 반복처리
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);    // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // 텍스처 filtering 정의 - 텍스처의 텍셀의 갯수가 모델의 픽셀 갯수보다 작거나 많을 때 어떻게 보간처리 할 것인가?
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 텍스처의 상하를 뒤집는다 (텍스처는 gl좌표계의 y축 반대라서...)
    stbi_set_flip_vertically_on_load(true);
    int texture_width, texture_height, nrChannels;
    // texture 읽어오기
    unsigned char *data = stbi_load(
                                    "/Users/beom.93/open_gl/c/OpenGL/OpenGL/res/texture/uvchecker.jpg",
                                    &texture_width,
                                    &texture_height,
                                    &nrChannels,
                                    0);
    // 텍스처 버퍼 바인드 및 데이트 전달
    unsigned int TEXTURE;
    glGenTextures(1, &TEXTURE);
    glBindTexture(GL_TEXTURE_2D, TEXTURE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_width, texture_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    // 텍스처 데이터 클리어
    stbi_image_free(data);
    
    
    std::vector<unsigned> vaos = initModel();
    // 초기화 후 바로 제거함. 드로우할 때 활성화 할것임.
    glBindTexture(GL_TEXTURE_2D, 0);
   
    
    
    while(!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
    
        processInput(window);
        glClear(GL_COLOR_BUFFER_BIT);
        shader.Bind();
        glBindTexture(GL_TEXTURE_2D, TEXTURE);
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        shader.SetUniformMat4f("view_transform_mat", view);
        
        glm::mat4 perspective = glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.0f, 100.0f);
        shader.SetUniformMat4f("perspective_transform_mat", perspective);
        for(int i = 0; i<vaos.size(); i++)
        {
            glBindVertexArray(vaos[i]);
            glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(i, 0.0f, 0.0f));
            shader.SetUniformMat4f("world_tramsform_mat", transform);
    
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}


