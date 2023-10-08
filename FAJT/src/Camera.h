#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

class Camera {
public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = 90, float pitch = 0)
        : position(position), up(up), yaw(yaw), pitch(pitch) {
        updateCameraVectors();
    }

    glm::mat4 GetViewMatrix() {
        if (yaw == 0.0f && pitch == 0.0f) {
            //return glm::lookAt(position, position + glm::vec3(0.0f, 0.0f, 1.0f), up);
        }
        return glm::lookAt(position, position + front, up);
    }

    glm::mat4 GetProjectionMatrix(float aspectRatio) {
        return glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
    }

    void Move(glm::vec3 move) {
        //position = glm::vec3(position.x + move.x, position.y + move.y, position.z + move.z);
        position += move;
    }

    // Implement camera control functions (e.g., processInput)

private:
    glm::vec3 position;
    glm::vec3 front = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 up;
    float yaw;
    float pitch;
    float fov = 45.0f;
    float nearClip = 0.1f;
    float farClip = 100.0f;

    void updateCameraVectors() {
        // Calculate front vector based on yaw and pitch
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(front);
    }
};


/*class Camera {
public:
	Camera(Shader shaderProgram) {
		view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

		
		projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

		int viewLoc = glGetUniformLocation(shaderProgram.shaderProgramID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		int projectionLoc = glGetUniformLocation(shaderProgram.shaderProgramID, "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));


	}
private:
	glm::mat4 view;
	glm::mat4 projection;
};*/
