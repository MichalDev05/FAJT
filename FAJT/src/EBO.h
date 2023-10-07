#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class EBO {
public:
	EBO(GLuint* indices, GLsizeiptr size) {
		//Create 1 buffer and assign id to EBO
		glGenBuffers(1, &m_EBO);
		//Bind buffer to EBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		//Buffer verticies to GL_ELEMENT_ARRAY_BUFFER
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	}

	void Bind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	}
	void Unbind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	void Delete() {
		glDeleteBuffers(1, &m_EBO);
	}

public:
	GLuint m_EBO;
};