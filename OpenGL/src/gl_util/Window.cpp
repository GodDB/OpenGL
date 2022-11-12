//
//  Window.cpp
//  OpenGL
//
//  Created by beom.93 on 2022/11/12.
//

#include "Window.hpp"

#include <iostream>

Window::Window()
    :m_Width{ 800 }, m_Height{ 600 }
{
}

Window::Window(int windowWidth, int windowHeight)
    : m_Width{ windowWidth }, m_Height{ windowHeight }
{
}

Window::~Window()
{
    glfwDestroyWindow(m_MainWindow);
    glfwTerminate();
}

void Window::Initialize()
{
    /* Initialize the library */
    if (!glfwInit())
        return;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    m_MainWindow = glfwCreateWindow(m_Width, m_Height, "Hello World", NULL, NULL);
    if (!m_MainWindow)
    {
        glfwTerminate();
        return;
    }

    //추가된 코드, 실제 버퍼 크기를 가져옴(현재는 윈도우 크기와 같지만, 상황에 따라 다를 수 있음)
    glfwGetFramebufferSize(m_MainWindow, &m_BufferWidth, &m_BufferHeight);

    /* Make the window's context current */
    glfwMakeContextCurrent(m_MainWindow);

    glfwSwapInterval(1); //1이면 vsync rate와 같은 속도로 화면 갱신

        // glfwMakeContextCurrent가 호출된 후에 glewInit이 수행되어야 함
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error\n";
    }

    glViewport(0, 0, m_BufferWidth, m_BufferHeight);

    std::cout << glGetString(GL_VERSION) << std::endl; //내 플랫폼의 GL_Version 출력해보기

    //알파 채널 처리 방법 (chapter 10에서 다룰 예정)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

