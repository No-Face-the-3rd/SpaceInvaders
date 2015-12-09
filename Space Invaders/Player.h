#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include "Game Object.h"
class Player : public gameObject
{
public:
	GLfloat health, energy, damageDelay, shotDelay[2], damageTimer;
	gameObject Shield;

	Texture2D bars;

	Player();
	~Player();
	
	void update(GLfloat dt);
	void draw(spriteRenderer & renderer);
	void init();
};

#endif