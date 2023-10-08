#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Camera.h"

class InputManager {
public:
	void ManageInput(GLFWwindow* window, float deltaTime);
	void SetCamera(Camera* camera) { m_Camera = camera; }
private:
	Camera* m_Camera;

};
