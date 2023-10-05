#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h";
#include "VBO.h";
#include "EBO.h";
#include "VAO.h";


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



	//Create Vertex Buffer Object
	VBO VBO1(vertices, sizeof(vertices));
	VBO1.Bind();

	//Create Vertex Array Object
	VAO VAO1;
	VAO1.Bind();

	//Create Element Buffer Object
	EBO EBO1(indices, sizeof(indices));
	EBO1.Bind();
	

	///---------------------Shaders------------------------
	Shader shaderProgram("res/shaders/default.vert", "res/shaders/default.frag");
	///----------------------------------------------------

	//specify opengl implementation
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//enable opengl implementation
	glEnableVertexAttribArray(0);

	//Activate shaderProgram
	shaderProgram.Activate();


	while (!glfwWindowShouldClose(window)) {
		// Set background color
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Use ShaderProgram
		shaderProgram.Activate();
		//Bind VAO
		VAO1.Bind();
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