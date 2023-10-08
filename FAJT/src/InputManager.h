#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Camera.h"
#include "Player.h"

class InputManager {
public:
	void ManageInput(GLFWwindow* window, float deltaTime);
	void SetCamera(Camera* camera) { m_Camera = camera; }
	void SetPlayer(Player* player) { m_Player = player; }
private:
	Camera* m_Camera;
	Player* m_Player;
	float m_DeadZones = 0.1f;
	float m_YDeadZones = 0.1f;


};
