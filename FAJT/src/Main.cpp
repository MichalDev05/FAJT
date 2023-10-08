#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "InputManager.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float deltaTime = 0.0f;
float lastFrame = 0.0f;

InputManager inputManager;

int main() {
	std::cout << "Hello World!";

	/*float vertices[] = {
		// positions          // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   0.0f, 1.0f,    // top left
	};*/

	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};


	float bgVertices[] = {
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	};

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  0.0f, -15.0f),
		glm::vec3(-1.5f, -0.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3,    // second triangle
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
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, 1280, 720);


	// Create Vertex Buffer Objects
	VBO VBO1(vertices, sizeof(vertices));
	VBO VBO2(bgVertices, sizeof(bgVertices));

	// Create Vertex Array Objects
	VAO VAO1;
	VAO VAO2;

	// Configure VAO1 for the 'vertices'
	VAO1.Bind();
	VBO1.Bind();
	int vertexValuesCount = 5;
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexValuesCount * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vertexValuesCount * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// Configure VAO2 for the 'bgVertices'
	VAO2.Bind();
	VBO2.Bind();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexValuesCount * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vertexValuesCount * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);



	///---------------------Textures-----------------------
	//Generate texture
	Texture texture("res/textures/ShrekProfile.jpg");

	///---------------------Shaders------------------------
	//Shader shaderProgram("res/shaders/default.vert", "res/shaders/default.frag");
	Shader shaderProgram("res/shaders/textured.vert", "res/shaders/textured.frag");
	Shader shaderProgram2("res/shaders/default.vert", "res/shaders/default.frag");

	//Activate shaderProgram
	shaderProgram.Activate();

	///----------------------------------------------------



	///-------------------Camera/View----------------------
	Camera camera(glm::vec3(0.0f, 0.0f, -20.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90, 0);

	inputManager.SetCamera(&camera);


	///----------------------------------------------------

	//specify opengl implementation
	//number of values for 1 vertex
	//int vertexValuesCount = 5;
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexValuesCount * sizeof(float), (void*)0);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vertexValuesCount * sizeof(float), (void*)(3 * sizeof(float)));
	//enable opengl implementation
	//glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);



	while (!glfwWindowShouldClose(window)) {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;


		inputManager.ManageInput(window, deltaTime);

		// Set background color
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		//glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 transform = glm::mat4(1.0f);
		glm::mat4 projection = camera.GetProjectionMatrix(1280.0f / 720.0f);

		// Use ShaderProgram
		shaderProgram.Activate();
		shaderProgram.setMat4("view", view);
		shaderProgram.setMat4("projection", projection);
		shaderProgram2.Activate();
		shaderProgram2.setMat4("view", view);
		shaderProgram2.setMat4("projection", projection);
		//shaderProgram.setMat4("transform", transform);

		VAO1.Bind();
		int j = 3;
		for (unsigned int i = 0; i < 10; i++)
		{
			if (i < j) shaderProgram.Activate();
			if (i >= j) shaderProgram2.Activate();

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			if (i < j) shaderProgram.setMat4("transform", model);
			if (i >= j) shaderProgram2.setMat4("transform", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		//Bind VAO
		VAO2.Bind();
		shaderProgram.Activate();
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0, -2, 0));
		model = glm::scale(model, glm::vec3(10, 10, 10));
		shaderProgram.setMat4("transform", model);
		glDrawArrays(GL_TRIANGLES, 0, 12);
		//Set polygon render mode (wireframe)
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//Draw triangles
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//Swap back and front buffer
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;

}