//
//  main.cpp
//  OpenGL
//
//  Created by beom.93 on 2022/11/05.
//
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

// gl 렌더링의 옛날 버전으로 삼각형 그려보기.
int main() {
    GLFWwindow* window;
    
    if(!glfwInit()) {
        //fail gl initialize
        return -1;
    }
    
    // GL window 생성
    window = glfwCreateWindow(640, 480, "Hello open gl", NULL, NULL);
    
    // gpu 연산의 결과는 window로 렌더링 되도록 설정
    glfwMakeContextCurrent(window);
    
    // glew가 이니셜라이즈 되었는가?
    if(glewInit() != GLEW_OK) {
        return -1;
    }
    
    // glfw window가 종료될 때 까지 무한 반복
    while (!glfwWindowShouldClose(window)) {
        
        glClear(GL_COLOR_BUFFER_BIT); // 기존 렌더링된것들을 날린다.
        
        glBegin(GL_TRIANGLES); //삼각형
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.5f, -0.5f);
        
        glEnd();
        
        // gl은 double buffer방식을 사용한다.
        // 그래서 백그라운드에 있는 buffer에 위의 삼각형이 그려지고,
        // 이 swap buffer함수를 통해 bg에 있는 buffer를 fg로 스와핑 시키는 작업을 한다.
        glfwSwapBuffers(window);

        // 인풋을 받기 위한 함수 (키보드, 마우스 등)
        glfwPollEvents();
    }
    
    // gl fw 종료
    glfwTerminate();
    return 0;

}
