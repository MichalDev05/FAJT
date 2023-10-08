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



    int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
    //std::cout << "Joistick: " << present << "\n";
    if (present == 1) {
        float moveX = 0;
        int axesCount;
        const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);

        if (axes[0] >= m_DeadZones || axes[0] <= -m_DeadZones) {
            moveX = -axes[0];
        }

        if (axes[1] <= -m_YDeadZones && m_Player->IsGrounded()) {
            m_Player->Jump();
        }
        //std::cout << "Joistick Axes: " << axesCount << "\n";
        //std::cout << "Joistick LefStick X: " << axes[0] << "\n";
        //std::cout << "Joistick LefStick Y: " << axes[1] << "\n";
        //std::cout << "Joistick RightStick X: " << axes[2] << "\n";
        //std::cout << "Joistick RightStick Y: " << axes[5] << "\n";
        int buttonsCount;
        const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonsCount);
        if (GLFW_PRESS == buttons[1])
            std::cout << "Joistick Button X" << "\n";
        if (GLFW_PRESS == buttons[2])
            std::cout << "Joistick Button Circle" << "\n";
        if (GLFW_PRESS == buttons[3])
            std::cout << "Joistick Button Triangle" << "\n";
        if (GLFW_PRESS == buttons[0])
            std::cout << "Joistick Button Square" << "\n";
        if (GLFW_PRESS == buttons[15]) // >
            moveX = -1;
        if (GLFW_PRESS == buttons[17]) // <
            moveX = 1;
        if (GLFW_PRESS == buttons[14] && m_Player->IsGrounded()) // ^
            m_Player->Jump();


        std::cout << moveX << "\n";
        m_Player->Move(glm::vec3(1, 0, 0) * moveX, deltaTime);
    }

}