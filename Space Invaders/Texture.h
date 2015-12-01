#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>


class Texture2D
{
public:
	GLuint ID;
	GLuint width, height;
	GLuint internalFormat, imageFormat, wrapS, wrapT, filterMin, filterMax;
	
	Texture2D();

	void generate(GLuint widthIn, GLuint heightIn, unsigned char *data);

	void bind() const;
};

#endif