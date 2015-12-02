#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include "Game Object.h"
class Player : public gameObject
{
public:
	GLfloat health, energy, rotationDelay, shotDelay[2];
	gameObject Shield;

	Player();
	~Player();
	
	void update(GLfloat dt);
	void draw(spriteRenderer & renderer);
	void move();
	void init();
};

#endif