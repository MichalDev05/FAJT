#pragma once
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

	//Activate shaderProgram
	void Activate();
	//Deletes shaderProgram
	void Delete();
};