#pragma once
#include<glm/glm.hpp>
#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

std::string GetFileContent(const char* path);

class Shader
{
public:
	//Create shaderProgramID
	GLuint shaderProgramID;

	Shader(const char* vertexFile, const char* fragmentFile);

	void Shader::setMat4(const std::string& name, const glm::mat4& matrix) const;

	//Activate shaderProgram
	void Activate();
	//Deletes shaderProgram
	void Delete();
};