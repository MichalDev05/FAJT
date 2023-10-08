#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Player {
public:
    Player(glm::vec3 pos = glm::vec3(0, 0, 0), float groundPos = -5.0f) {
        position = pos;
        m_GroundPos = groundPos;
    }

    glm::mat4 GetPositionMatrix() {
        return glm::translate(glm::mat4(1.0f), position);
    }

    void Move(glm::vec3 move, float deltaTime);
    
    void Jump();
    
    void SetPosition(glm::vec3 pos) {
        position = pos;
    }

    bool IsGrounded() {
        return m_IsGrounded;
    }

    void Update(float deltaTime);
private:
	glm::vec3 position;
    float m_GroundPos;
    float m_YVelocity;
    float m_Gravity = -90.0f;
    float m_JumpVelocity = 35;
    float m_Speed = 10;
    bool m_IsGrounded;
};