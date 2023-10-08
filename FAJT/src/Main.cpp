#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Player.h"
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

	std::vector<VAO> VAOs;
	std::vector<VBO> VBOs;
	std::vector<Texture> textures;
	std::vector<Shader> shaders;

	Player player(glm::vec3(0.0f, 10, -4.0f), -2.5);

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

	float playerVertices[] = {
		-0.5f,  0.5f, 0.0f,   0.0f, 1.0f,    // top left
		0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // top right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f,   // bottom left

		0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f   // bottom left
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
	VBOs.push_back(VBO(vertices, sizeof(vertices)));
	VBOs.push_back(VBO(bgVertices, sizeof(bgVertices)));
	VBOs.push_back(VBO(playerVertices, sizeof(playerVertices)));

	// Create Vertex Array Objects
	for (int i = 0; i < VBOs.size(); i++) {
		VAOs.push_back(VAO());
	}

	for (int i = 0; i < VBOs.size(); i++) {
		VAOs[i].Bind();
		VBOs[i].Bind();
		int vertexValuesCount = 5;
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexValuesCount * sizeof(float), (void*)0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vertexValuesCount * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
	}



	///---------------------Textures-----------------------
	//Generate texture
	textures.push_back(Texture("res/textures/ShrekProfile.jpg"));
	textures.push_back(Texture("res/textures/uvTest.png"));
	textures.push_back(Texture("res/textures/training_hexas.png"));
	textures.push_back(Texture("res/textures/HexagonGrid.jpg"));
	textures.push_back(Texture("res/textures/HexagonGrid_2.jpg"));
	textures.push_back(Texture("res/textures/HexagonGrid_3.jpg"));
	textures.push_back(Texture("res/textures/Grid1.png"));

	///---------------------Shaders------------------------
	shaders.push_back(Shader("res/shaders/textured.vert", "res/shaders/textured.frag"));
	shaders.push_back(Shader("res/shaders/default.vert", "res/shaders/default.frag"));
	shaders.push_back(Shader("res/shaders/tiled.vert", "res/shaders/tiledTex.frag"));

	///----------------------------------------------------



	///-------------------Camera/View----------------------
	Camera camera(glm::vec3(0.0f, 0.0f, -20.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90, 0);

	inputManager.SetCamera(&camera);
	inputManager.SetPlayer(&player);


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

		player.Update(deltaTime);
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
		shaders[0].Activate();
		shaders[0].setMat4("view", view);
		shaders[0].setMat4("projection", projection);
		shaders[1].Activate();
		shaders[1].setMat4("view", view);
		shaders[1].setMat4("projection", projection);
		shaders[2].Activate();
		shaders[2].setMat4("view", view);
		shaders[2].setMat4("projection", projection);
		//shaderProgram.setMat4("transform", transform);

		VAOs[0].Bind();
		textures[0].Bind();
		int j = 3;
		for (unsigned int i = 0; i < 10; i++)
		{
			if (i < j) shaders[0].Activate();
			if (i >= j) shaders[1].Activate();

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			if (i < j) shaders[0].setMat4("transform", model);
			if (i >= j) shaders[1].setMat4("transform", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		//BG
		VAOs[1].Bind();
		textures[3].Bind();
		textures[4].Bind();
		textures[5].Bind();
		textures[6].Bind();
		shaders[2].Activate();
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0, 45, -20));
		model = glm::scale(model, glm::vec3(100, 100, 100));
		shaders[2].setMat4("transform", model);
		glDrawArrays(GL_TRIANGLES, 0, 12);
		
		//Player
		VAOs[2].Bind();
		textures[1].Bind();
		shaders[0].Activate();
		model = player.GetPositionMatrix();
		model = glm::scale(model, glm::vec3(5, 5, 5));
		shaders[0].setMat4("transform", model);
		glDrawArrays(GL_TRIANGLES, 0, 6);

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