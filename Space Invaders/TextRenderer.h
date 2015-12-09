#pragma once
#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <map>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Texture.h"
#include "Shader.h"

struct Character
{
	GLuint TextureID;
	glm::ivec2 size;
	glm::ivec2 Bearing;
	GLuint advance;
};

class TextRenderer
{
private:
	GLuint VAO, VBO;
public:
	std::map<GLchar, Character> Characters;

	Shader textShader;

	TextRenderer(GLuint width, GLuint height);

	~TextRenderer();

	void load(std::string font, GLuint fontSize);
	void renderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color = glm::vec3(1.0f));

};

#endif