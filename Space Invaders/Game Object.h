#pragma once

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Texture.h"
#include "Sprite Renderer.h"


class Game;

class gameObject
{
public:
	
	static Game *&gameState()
	{
		static Game *gameState;
		return gameState;
	}


	glm::vec2 position, speed;
	glm::vec3 color;
	GLfloat radius, rotation;

	Texture2D texture;


	gameObject();
	gameObject(glm::vec2 pos, GLfloat rad, Texture2D tex, glm::vec3 colorIn = glm::vec3(1.0f), glm::vec2 spd = glm::vec2(0.0f, 0.0f), GLfloat angle = 0.0f);

	~gameObject();
	virtual void draw(spriteRenderer &renderer);
	virtual void update(GLfloat dt);
	virtual void move() {};
};

#endif