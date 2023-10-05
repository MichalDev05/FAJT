#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";


int main() {
	std::cout << "Hello World!";

	float vertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};
	
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1280, 720, "FAJT", NULL, NULL);
	if (window == NULL) {
		std::cerr << "ERROR: Window was not created!";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);


	gladLoadGL();
	glViewport(0, 0, 800, 800);

	///---------------------Vertex Buffer------------------
	//Create Vertex Buffer Object
	GLuint VBO;
	//Create 1 buffer and assign id to VBO
	glGenBuffers(1, &VBO);
	//Bind buffer to VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Buffer verticies to GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	///----------------------------------------------------

	///---------------------Vertex Array------------------
	//Create Vertex Array Object
	GLuint VAO;
	//Create 1 array and assign id to VAO
	glGenVertexArrays(1, &VAO);
	//Bind VAO
	glBindVertexArray(VAO);
	///----------------------------------------------------

	///---------------------Element Buffer------------------
	//Create Element Buffer Object
	GLuint EBO;
	//Create 1 buffer and assign id to EBO
	glGenBuffers(1, &EBO);
	//Bind buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//Buffer elements
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	///---------------------Shaders------------------------
	//Create vertexShader
	GLuint vertexShader;
	//Set vertexShader to id
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//Set vertexShaderSource into vertexShader id
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//Compile shader into code
	glCompileShader(vertexShader);

	//Check for shader compile errors
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//Create fragmentShader
	GLuint fragmentShader;
	//Set fragmentShader to id
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//Set fragmentShaderSource into fragmentShader id
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//Compile shader to code
	glCompileShader(fragmentShader);
	///-------------------------------------------------------

	///------------------Shader Program-----------------------
	//Create shaderProgram
	GLuint shaderProgram;
	//Set shdarProgram to new id
	shaderProgram = glCreateProgram();
	//Attach shaders
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);


	//After linking shders to program we dont need them, so we delete them
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	///----------------------------------------------------

	//specify opengl implementation
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//enable opengl implementation
	glEnableVertexAttribArray(0);

	//Activate shaderProgram
	glUseProgram(shaderProgram);


	while (!glfwWindowShouldClose(window)) {
		// Set background color
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Use ShaderProgram
		glUseProgram(shaderProgram);
		//Bind VAO
		glBindVertexArray(VAO);
		//Set polygon render mode (wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//Draw triangles
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//Swap back and front buffer
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;

}