//
//  Camera.hpp
//  OpenGL
//
//  Created by beom.93 on 2022/11/12.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <stdio.h>

#include "glm.hpp"
#include "matrix_transform.hpp"

//WASD로 움직이고, 마우스로 둘러보는 카메라의 구현

class Camera
{
public:
    Camera();
    Camera(
           glm::vec3 initEye,
           glm::vec3 initUp,
           float initYaw,
           float initPitch,
           float initMoveSpeed,
           float initTurnSpeed);
    ~Camera();

    void KeyControl(bool *keys, float deltaTime);
    void MouseControl(float xChange, float yChange);

    glm::mat4 calculateViewMatrix();
private:
    glm::vec3 m_Eye;
    glm::vec3 m_Front;
    glm::vec3 m_Up;
    glm::vec3 m_Right;
    float m_Yaw;
    float m_Pitch;
    float m_MoveSpeed;
    float m_TurnSpeed;

    void Update();
    
};
#endif /* Camera_hpp */
