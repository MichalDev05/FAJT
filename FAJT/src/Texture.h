#pragma once
#include <glad/glad.h>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION 
#include <stb_image.h>

class Texture {
public:
	Texture(char* filePath) {
		this->m_FilePath = filePath;
		//So texture will not be upside down
		stbi_set_flip_vertically_on_load(true);

		//Load image
		m_DataBuffer = stbi_load(m_FilePath, &m_Width, &m_Height, &m_NrChannels, 0);

		if (!m_DataBuffer) {
			std::cerr << "Failed to load texture" << "\n";
			stbi_image_free(m_DataBuffer);
			return;
		}

		//Set texture options
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


		//Generate textureID
		glGenTextures(1, &m_TextureID);

		//Bind texture
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		//Generate texture from data
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_DataBuffer);
		glGenerateMipmap(GL_TEXTURE_2D);


		//Remove image from memory
		stbi_image_free(m_DataBuffer);
	}

	void Bind() {
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
	}
	
	void Unbind() {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Delte() {
		glDeleteTextures(1, &m_TextureID);
	}
private:
	GLuint m_TextureID;

	int m_Width;
	int m_Height;
	int m_NrChannels;
	const char* m_FilePath;

	unsigned char* m_DataBuffer;
};
