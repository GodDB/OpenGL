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
    
    // 벡터의 외적이 바깥을 가르키는 것만 그린다.
    glEnable(GL_CULL_FACE);
    // 삼각형 정점 데이터 (3차원)
    
    // 이건 그려지지 않음. 이 면은 안을 가르키기 때문에 그려지지 않는다. (외적의 결과)
    // float triangle_pos[9] = {
    //     -0.5f, -0.5f, 0.0f,
    //     0.0f, 0.5f, 0.0f,
    //     0.5f, -0.5f, 0.0f
    //  };
    
    float triangle_pos[9] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };
        
    unsigned int bufferId; // 생성할 버퍼의 아이디
    glGenBuffers(1, &bufferId); // 버퍼 1개 생성 및 bufferId 전달
    glBindBuffer(GL_ARRAY_BUFFER, bufferId); // 해당 buffer id를 액티브 상태로 변경 (array를 받는 형태)
    
    // 버퍼에 데이터 전달
    glBufferData(
                 GL_ARRAY_BUFFER, // array 형태로 전달할 것임을 명시,
                 9 * sizeof(float), // 데이터의 크기 전달
                 triangle_pos, // 데이터 포인터 전달
                 GL_STATIC_DRAW // 데이터의 변경이 적을 것임을 명시 (렌더링 효율성 증가)
                 );
    
    // 몇번째 Location의 attribute를 활성화 할 것인지
    glEnableVertexAttribArray(0);
    // 데이터 해석 방법 전달
    glVertexAttribPointer(
                          0, // 0번째 location의 attribute의 해석 방법
                          3, // 각 데이터가 몇개 단위로 이루어져 있는지
                          GL_FLOAT, // 데이터 타입
                          GL_FALSE, // 정규화가 필요한지
                          sizeof(float) * 3, // 한 단위의 데이터를 읽을 때 마다, 얼마나 건너 뛰어야 하는지
                          0 // 첫 데이터가 몇 바이트로부터 시작하는지
                          );
    
    // glfw window가 종료될 때 까지 무한 반복
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT); // 기존 렌더링된것들을 날린다.
        
        // vertex shader를 설정하지 않았는데도, 삼각형이 나옴!
        // 이유는 GPU 드라이버에서 자동 설정이 되어있기 때문임.
        glDrawArrays(
                     GL_TRIANGLES,
                     0,
                     3
                     );
        
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
