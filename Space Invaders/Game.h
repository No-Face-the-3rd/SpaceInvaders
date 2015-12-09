#pragma once

#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <vector>

#include "Player.h"
#include "Enemy.h"


enum gameStateEnum { SPLASH,MENU_INIT,MENU,PLAY_INIT,PLAY,PAUSE,LOSE};

class Game
{
public:
	gameStateEnum gs;
	GLuint width, height;
	GLboolean keys[1024], keysProcessed[1024], mouse[3], mouseProcessed[3];
	GLuint enemyAmt, playerKills, killAfterChange;
	float playerMaxHP, playerMaxEnergy;
	glm::vec2 mousePos;
	std::vector<gameObject> playerBullets, enemyBullets;
	std::vector<Enemy> enemies;
	std::vector<int> pBulletDelete, eBulletDelete, eDelete;
	gameObject staticVisuals[3], buttons[4];

	Game();
	Game(GLuint widthIn, GLuint heightIn);
	~Game();
	Player player;

	void init();

	void processInput(GLfloat dt);
	void update(GLfloat dt);
	void render();
	void enterGame();
	void spawnBullet(std::vector<gameObject> &bullets, GLfloat angle, glm::vec3 colorIn, glm::vec2 pos, GLfloat radius, glm::vec2 spd);
	void spawnEnemy();
};

#endif

