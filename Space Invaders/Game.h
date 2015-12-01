#pragma once

#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>

#include <GLFW/glfw3.h>

enum gameState { INIT,MENU,ENTER_GAME,PLAY,PAUSE,RESULT};

class Game
{
public:
	gameState gs;
	GLuint width, height;
	GLboolean keys[1024], keysProcessed[1024];

	Game(GLuint widthIn, GLuint heightIn);
	~Game();

	void init();

	void processInput(GLfloat dt);
	void update(GLfloat dt);
	void render();
};

#endif

