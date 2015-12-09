#include "Enemy.h"
#include "Game.h"

#include <math.h>

#ifndef PI
#define PI 3.1415926535f
#endif

#ifndef CORRECTION
#define CORRECTION PI/2
#endif

#include <iostream>

Enemy::Enemy() : shotDelay(0.75f)
{
}


Enemy::~Enemy()
{
}


void Enemy::update(GLfloat dt)
{
	GLfloat num = gameObject::gameState()->player.position.y - this->position.y, den = gameObject::gameState()->player.position.x - this->position.x;
	if (!den)
	{
		if (num >= 0)
			this->rotation = PI;
		else if (num < 0)
			this->rotation = 0.0f;
	}
	else
	{
		this->rotation = atan(num / den) - CORRECTION;
		if (den > 0)
			this->rotation += PI;
	}
	num *= -1;
	den *= -1;
	float testAngle;
	if (!den)
	{
		if (num >= 0)
			testAngle = PI;
		else if (num < 0)
			testAngle = 0.0f;
	}
	else
	{
		testAngle = atan(num / den) - CORRECTION;
		if (den > 0)
			testAngle += PI;
	}
	float distToPlayer = glm::distance(this->position, gameObject::gameState()->player.position);
	if (distToPlayer <= this->radius + gameObject::gameState()->player.radius * 1.5f && std::abs(testAngle - gameObject::gameState()->player.Shield.rotation) < PI / 2 && gameObject::gameState()->player.energy >= 20 && !dead)

	{
		gameObject::gameState()->player.energy -= 20.0f;
		procKill();
		gameObject::gameState()->player.Shield.color = glm::vec3(0.0f, 0.0f, 1.0f);
	}
	else if (distToPlayer <= this->radius + gameObject::gameState()->player.radius && gameObject::gameState()->player.damageTimer <= 0.0f && !dead)
	{
		gameObject::gameState()->player.health -= 28.0f;
		procKill();
		gameObject::gameState()->player.color = glm::vec3(1.0f, 0.5f, 0.5f);
		gameObject::gameState()->player.damageTimer = 0.25f;
	}

	for (int i = 0; i < gameObject::gameState()->playerBullets.size(); ++i)
	{
		if (glm::distance(this->position, gameObject::gameState()->playerBullets[i].position) <= this->radius + gameObject::gameState()->playerBullets[i].radius)
		{
			procKill();
			gameObject::gameState()->pBulletDelete.emplace_back(i);
			gameObject::gameState()->player.energy += 2.5f;
		}
	}
	if (!den)
	{
		if (num >= 0)
			testAngle = PI;
		else if (num < 0)
			testAngle = 0.0f;
	}
	else
	{
		testAngle = atan(num / den);
		if (den < 0)
			testAngle += PI;
	}
	if (testAngle < 0)
		testAngle += 2 * PI;

	float scale = 0.95f;
	if (aiTimer <= 0.0f)
	{
		aiTimer = 0.15f;
		if (clockwise)
			targetLoc = gameObject::gameState()->player.position + glm::vec2(scale * distToPlayer * cos(testAngle - (10.0f * PI / 180.0f)), scale * distToPlayer * sin(testAngle - (10.0f * PI / 180.0f)));
		else
			targetLoc = gameObject::gameState()->player.position + glm::vec2(scale * distToPlayer * cos(testAngle + (10.0f * PI / 180.0f)), scale * distToPlayer * sin(testAngle + (10.0f * PI / 180.0f)));
	}
	
	aiTimer -= dt;

	if (this->position.x < this->targetLoc.x)
		this->position.x += this->speed.x * dt;
	else if (this->position.x>this->targetLoc.x)
		this->position.x -= this->speed.x * dt;

	if (this->position.y < this->targetLoc.y)
		this->position.y += this->speed.y * dt;
	else if (this->position.y>this->targetLoc.y)
		this->position.y -= this->speed.y * dt;

	if (this->position.y <= this->radius)
		this->position.y = this->radius + 5.0f;
	if (this->position.x <= this->radius)
		this->position.x = this->radius + 5.0f;

	if (this->position.y >= gameObject::gameState()->height - this->radius - 5.0f)
		this->position.y = gameObject::gameState()->height - this->radius - 5.0f;
	if (this->position.x >= gameObject::gameState()->width - this->radius - 5.0f)
		this->position.x = gameObject::gameState()->width - this->radius - 5.0f;

	shotDelay -= dt;
	if (shotDelay <= 0.0f)
	{
		gameObject::gameState()->spawnBullet(gameObject::gameState()->enemyBullets, 0.0f , glm::vec3(1.0f, 0.0f, 0.0f), position + glm::vec2(radius * cos(rotation - PI / 2.0f), radius * sin(rotation - PI / 2.0f)), radius / 10.0f, glm::vec2(200.0f * cos(rotation - PI / 2.0f), 200.0f * sin(rotation - PI / 2.0f)));
		shotDelay = 0.75f;
	}
}


void Enemy::procKill()
{
	this->dead = true;
	this->aiTimer = 0.001f;
}