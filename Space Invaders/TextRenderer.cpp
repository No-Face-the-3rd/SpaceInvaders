//#include "TextRenderer.h"
//
//#include <iostream>
//#include <glm/gtc/matrix_transform.hpp>
//#include <ft2build.h>
//#include FT_FREETYPE_H
//
//#include "Resource Manager.h"
//
//
//
//
//TextRenderer::TextRenderer(GLuint width, GLuint height)
//{
//	this->textShader = ResourceManager
//		::loadShader("shaders/text.vs", "shaders/text.frag", nullptr, "text");
//	this->textShader.setMatrix4("projection", glm::ortho(0.0f, static_cast<GLfloat>(width), static_cast<GLfloat>(height), 0.0f), GL_TRUE);
//	this->textShader.setInteger("text", 0);
//
//	glGenVertexArrays(1, &this->VAO);
//	glGenBuffers(1, &this->VBO);
//	glBindVertexArray(this->VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//}
//
//TextRenderer::~TextRenderer()
//{
//}
//
//void TextRenderer::load(std::string font, GLuint fontSize)
//{
//	this->Characters.clear();
//
//	FT_Library ft;
//
//	if (FT_Init_FreeType(&ft))
//		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
//
//	FT_Face face;
//	if (FT_New_Face(ft, font.c_str(), 0, &face))
//		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
//
//	FT_Set_Pixel_Sizes(face, 0, fontSize);
//
//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//
//	for (GLubyte c = 0; c < 128; ++c)
//	{
//		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
//		{
//			std::cout << "ERROR::FREETYPE: Failed to load glyph" << std::endl;
//			continue;
//		}
//
//		GLuint texture;
//
//
//		glGenTextures(1, &texture);
//		glBindTexture(GL_TEXTURE_2D, texture);
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
//
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//		Character character = { texture, glm::ivec2(face->glyph->bitmap.width,face->glyph->bitmap.rows),glm::ivec2(face->glyph->bitmap_left,face->glyph->bitmap_top),face->glyph->advance.x };
//		Characters.insert(std::pair<GLchar, Character>(c, character));
//
//		glBindTexture(GL_TEXTURE_2D, 0);
//
//		FT_Done_Face(face);
//		FT_Done_FreeType(ft);
//	}
//}
//
//void TextRenderer::renderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
//{
//}
