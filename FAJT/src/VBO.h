#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VBO {
public:
	VBO(GLfloat* vertices, GLsizeiptr size) {
		//Create 1 buffer and assign id to VBO
		glGenBuffers(1, &m_VBO);
		//Bind buffer to VBO
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		//Buffer verticies to GL_ARRAY_BUFFER
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	void Bind() {
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	}
	void Unbind() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void Delete() {
		glDeleteBuffers(1, &m_VBO);
	}

public:
	GLuint m_VBO;
};