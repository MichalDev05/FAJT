#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VAO {
public:
	VAO() {
		//Create 1 array and assign id to VAO
		glGenVertexArrays(1, &m_VAO);
		//Bind VAO
		glBindVertexArray(m_VAO);
	}

	void Bind() {
		glBindVertexArray(m_VAO);
	}
	void Unbind() {
		glBindVertexArray(0);
	}
	void Delete() {
		glDeleteVertexArrays(1, &m_VAO);
	}

public:
	GLuint m_VAO;
};