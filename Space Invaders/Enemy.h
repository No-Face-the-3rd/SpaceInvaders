#pragma once

#ifndef ENEMY_H
#define ENEMY_H

#include "Game Object.h"

class Enemy : public gameObject
{
public:
	float aiTimer, shotDelay;
	glm::vec2 targetLoc;
	bool dead, clockwise;

	Enemy();
	~Enemy();

	void update(GLfloat dt);
	void procKill();
};

#endif