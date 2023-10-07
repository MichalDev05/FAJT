#include "Shader.h"

std::string GetFileContent(const char* path)
{
	std::ifstream inputStream(path, std::ios::binary);
	if (inputStream)
	{
		std::string content;
		inputStream.seekg(0, std::ios::end);
		content.resize(inputStream.tellg());
		inputStream.seekg(0, std::ios::beg);
		inputStream.read(&content[0], content.size());
		inputStream.close();
		return content;
	}
	throw(errno);
	
}


Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	//Get Code from file
	std::string vertexShaderCode = GetFileContent(vertexFile);
	std::string fragmentShaderCode = GetFileContent(fragmentFile);

	//Convert code to char array
	const char* vertexShaderSource = vertexShaderCode.c_str();
	const char* fragmentShaderSource = fragmentShaderCode.c_str();


	///--------------VERTEX SHADER------------------
	//Create vertexShader
	GLuint vertexShader;
	//Set vertexShader to id
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//Set vertexShaderSource into vertexShader id
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//Compile shader into code
	glCompileShader(vertexShader);

	//Check for vertexShader compile errors
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//Clear vars
	success = 0;
	memset(infoLog, 0, sizeof(infoLog));
	///---------------------------------------------
	


	///-------------FRAGMENT SHADER-----------------
	//Create fragmentShader
	GLuint fragmentShader;
	//Set fragmentShader to id
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//Set fragmentShaderSource into fragmentShader id
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//Compile shader to code
	glCompileShader(fragmentShader);

	//Check for fragmentShader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	///---------------------------------------------

	///--------------SHADER PROGRAM-----------------
	//Set shaderProgram to new id
	shaderProgramID = glCreateProgram();
	//Attach shaders
	glAttachShader(shaderProgramID, vertexShader);
	glAttachShader(shaderProgramID, fragmentShader);
	glLinkProgram(shaderProgramID);


	//After linking shders to program we dont need them, so we delete them
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	///---------------------------------------------

}

void Shader::setMat4(const std::string& name, const glm::mat4& matrix) const
{
	glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
}

//Activate shaderProgram
void Shader::Activate()
{
	glUseProgram(shaderProgramID);
}

//Delete shaderProgram
void Shader::Delete()
{
	glDeleteProgram(shaderProgramID);
}
