#include "Resource Manager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <SOILsrc/SOIL.h>


std::map<std::string, Shader> ResourceManager::shaders;
std::map<std::string, Texture2D> ResourceManager::textures;

Shader ResourceManager::loadShader(const GLchar * vShaderFile, const GLchar * fShaderFile, const GLchar * gShaderFile, std::string name)
{
	shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
	return shaders[name];
}

Shader ResourceManager::getShader(std::string name)
{
	return shaders[name];
}

Texture2D ResourceManager::loadTexture(const GLchar * file, GLboolean alpha, std::string name)
{
	textures[name] = loadTextureFromFile(file, alpha);
	return textures[name];
}

Texture2D ResourceManager::getTexture(std::string name)
{
	return textures[name];
}

void ResourceManager::clear()
{
	for (auto iter : shaders)
	{
		glDeleteProgram(iter.second.ID);
	}
	for (auto iter : textures)
	{
		glDeleteTextures(1, &iter.second.ID);
	}
}

ResourceManager::ResourceManager()
{
}

Shader ResourceManager::loadShaderFromFile(const GLchar * vShaderFile, const GLchar * fShaderFile, const GLchar * gShaderFile)
{
	std::string vCode, fCode, gCode;
	try
	{
		std::ifstream vertexShaderFile(vShaderFile);
		std::ifstream fragmentShaderFile(fShaderFile);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();

		vertexShaderFile.close();
		fragmentShaderFile.close();

		vCode = vShaderStream.str();
		fCode = fShaderStream.str();

		if (gShaderFile)
		{
			std::ifstream geometryShaderFile(gShaderFile);
			std::stringstream gShaderStream;
			gShaderStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			gCode = gShaderStream.str();
		}
	}
	catch (std::exception e)
	{
		std::cout << "ERROR::SHADER: Failed to read shader files\n";
	}
	const GLchar *vShaderCode = vCode.c_str(), *fShaderCode = fCode.c_str(), *gShaderCode = gCode.c_str();
	Shader shader;
	shader.compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
	return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const GLchar * file, GLboolean alpha)
{
	Texture2D texture;
	if (alpha)
	{
		texture.internalFormat = GL_RGBA;
		texture.imageFormat = GL_RGBA;
	}

	int width, height;
	unsigned char *image = SOIL_load_image(file, &width, &height, 0, texture.imageFormat == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);

	texture.generate(width, height, image);
	SOIL_free_image_data(image);
	return texture;
}


