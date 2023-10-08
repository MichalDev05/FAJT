#include "InputManager.h"


void InputManager::ManageInput(GLFWwindow* window, float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = static_cast<float>(5 * deltaTime);
    //if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        //cameraPos += cameraSpeed * cameraFront;
    //if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        //cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        m_Camera->Move(glm::vec3(1, 0, 0) * cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        m_Camera->Move(glm::vec3(-1, 0, 0) * cameraSpeed);
}