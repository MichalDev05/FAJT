#include "Player.h"

void Player::Update(float deltaTime) {
	//std::cout << position.x << ", " << position.y << ", " << position.z << "\n";

	position.y += m_YVelocity * deltaTime;

	if (position.y > m_GroundPos) {
		//gravity
		m_YVelocity += m_Gravity * deltaTime;
		
		m_IsGrounded = false;
	}
	else {
		m_IsGrounded = true;
		position.y = m_GroundPos;
		if (m_YVelocity < 0)
		m_YVelocity = 0;
	}
}

void Player::Move(glm::vec3 move, float deltaTime) {

	position += move * m_Speed * deltaTime;
}

void Player::Jump() {
	if (IsGrounded())
		m_YVelocity = m_JumpVelocity;
}