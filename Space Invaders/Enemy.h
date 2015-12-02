#pragma once

#ifndef ENEMY_H
#define ENEMY_H

#include "Game Object.h"

class Enemy : public gameObject
{
public:
	float aiTimer;

	Enemy();
	~Enemy();

	void update();
	void move();
};

#endif