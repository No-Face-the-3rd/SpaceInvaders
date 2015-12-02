#pragma once

#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <vector>

#include "Player.h"
#include "Enemy.h"


enum gameStateEnum { SPLASH,MENU_INIT,MENU,PLAY_INIT,PLAY,PAUSE,ABOUT};

class Game
{
public:
	gameStateEnum gs;
	GLuint width, height;
	GLboolean keys[1024], keysProcessed[1024], mouse[3], mouseProcessed[3];
	GLuint enemyAmt, playerKills;
	glm::vec2 mousePos;
	std::vector<gameObject> playerBullets, enemyBullets;
	GLuint pBulletDelete, eBulletDelete;

	Game();
	Game(GLuint widthIn, GLuint heightIn);
	~Game();
	Player player;

	void init();

	void processInput(GLfloat dt);
	void update(GLfloat dt);
	void render();
	void enterGame();
	void SpawnBullet(std::vector<gameObject> &bullets, GLfloat angle, glm::vec3 colorIn, glm::vec2 pos, GLfloat radius, glm::vec2 spd);
};

#endif

