#include "Player.h"

#include "Resource Manager.h"

#include "Game.h"

#include <math.h>

#ifndef PI
#define PI 3.1415926535f
#endif

#ifndef CORRECTION
#define CORRECTION PI/2
#endif

Player::Player()
{
	this->position = glm::vec2(0.0f,0.0f);
	this->speed = glm::vec2(150.0f, 150.0f);
	this->color = glm::vec3(1.0f,1.0f,1.0f);
	this->radius = 25.0f;
	this->rotation = 0.0f;
	this->rotationDelay = 10.0f;
	this->health = 100.0f;
	this->energy = 100.0f;
	this->shotDelay[0] = 1.0f;
	this->shotDelay[1] = 1.0f;
	this->damageTimer = 0.0f;
}


Player::~Player()
{
}

void Player::update(GLfloat dt)
{
	Shield.position = this->position;
	Shield.radius = this->radius * (1.5f);
	GLfloat num = gameObject::gameState()->mousePos.y - this->position.y, den = gameObject::gameState()->mousePos.x - this->position.x;
	if (!den)
		if (num >= 0)
			Shield.rotation = 0.0f;
		else if (num < 0)
			Shield.rotation = PI;
		else;
	else
	{
		Shield.rotation = atan(num / den) - CORRECTION;
		if (den > 0)
			Shield.rotation += PI;
	}
	shotDelay[0] -= dt;
	shotDelay[1] -= dt;
	float bSpeed = 200.0f;
	if (gameObject::gameState()->mouse[GLFW_MOUSE_BUTTON_LEFT])
		if (!gameObject::gameState()->mouseProcessed[GLFW_MOUSE_BUTTON_LEFT])
			if (energy >= 10)
			{
				shotDelay[0] = 1.0f;
				energy -= 10;
				GLfloat tmpAngle = PI / 4;
				glm::vec3 color = glm::vec3(0.0f, 0.0f, 1.0f);
				gameObject::gameState()->spawnBullet(gameObject::gameState()->playerBullets, tmpAngle, color, glm::vec2(position.x + radius * cos(tmpAngle + CORRECTION), position.y + radius * sin(tmpAngle + CORRECTION)), radius / 10.0f, glm::vec2(bSpeed * cos(tmpAngle + CORRECTION), bSpeed * sin(tmpAngle + CORRECTION)));
				tmpAngle = 3 * PI / 4;
				gameObject::gameState()->spawnBullet(gameObject::gameState()->playerBullets, tmpAngle, color, glm::vec2(position.x + radius * cos(tmpAngle + CORRECTION), position.y + radius * sin(tmpAngle + CORRECTION)), radius / 10.0f, glm::vec2(bSpeed * cos(tmpAngle + CORRECTION), bSpeed * sin(tmpAngle + CORRECTION)));
				tmpAngle = 5 * PI / 4;
				gameObject::gameState()->spawnBullet(gameObject::gameState()->playerBullets, tmpAngle, color, glm::vec2(position.x + radius * cos(tmpAngle + CORRECTION), position.y + radius * sin(tmpAngle + CORRECTION)), radius / 10.0f, glm::vec2(bSpeed * cos(tmpAngle + CORRECTION), bSpeed * sin(tmpAngle + CORRECTION)));
				tmpAngle = 7 * PI / 4;
				gameObject::gameState()->spawnBullet(gameObject::gameState()->playerBullets, tmpAngle, color, glm::vec2(position.x + radius * cos(tmpAngle + CORRECTION), position.y + radius * sin(tmpAngle + CORRECTION)), radius / 10.0f, glm::vec2(bSpeed * cos(tmpAngle + CORRECTION), bSpeed * sin(tmpAngle + CORRECTION)));

			}
			else;
		else
		{
			if (energy >= 10 && shotDelay[0] <= 0.0f)
			{
				shotDelay[0] = 1.0f;
				energy -= 10;
				GLfloat tmpAngle = PI / 4;
				glm::vec3 color = glm::vec3(0.0f, 0.0f, 1.0f);
				gameObject::gameState()->spawnBullet(gameObject::gameState()->playerBullets, tmpAngle, color, glm::vec2(position.x + radius * cos(tmpAngle + CORRECTION), position.y + radius * sin(tmpAngle + CORRECTION)), radius / 10.0f, glm::vec2(bSpeed * cos(tmpAngle + CORRECTION), bSpeed * sin(tmpAngle + CORRECTION)));
				tmpAngle = 3 * PI / 4;
				gameObject::gameState()->spawnBullet(gameObject::gameState()->playerBullets, tmpAngle, color, glm::vec2(position.x + radius * cos(tmpAngle + CORRECTION), position.y + radius * sin(tmpAngle + CORRECTION)), radius / 10.0f, glm::vec2(bSpeed * cos(tmpAngle + CORRECTION), bSpeed * sin(tmpAngle + CORRECTION)));
				tmpAngle = 5 * PI / 4;
				gameObject::gameState()->spawnBullet(gameObject::gameState()->playerBullets, tmpAngle, color, glm::vec2(position.x + radius * cos(tmpAngle + CORRECTION), position.y + radius * sin(tmpAngle + CORRECTION)), radius / 10.0f, glm::vec2(bSpeed * cos(tmpAngle + CORRECTION), bSpeed * sin(tmpAngle + CORRECTION)));
				tmpAngle = 7 * PI / 4;
				gameObject::gameState()->spawnBullet(gameObject::gameState()->playerBullets, tmpAngle, color, glm::vec2(position.x + radius * cos(tmpAngle + CORRECTION), position.y + radius * sin(tmpAngle + CORRECTION)), radius / 10.0f, glm::vec2(bSpeed * cos(tmpAngle + CORRECTION), bSpeed * sin(tmpAngle + CORRECTION)));
			}
		}
	if(gameObject::gameState()->mouse[GLFW_MOUSE_BUTTON_RIGHT])
		if (!gameObject::gameState()->mouseProcessed[GLFW_MOUSE_BUTTON_RIGHT])
			if (energy >= 10)
			{
				shotDelay[1] = 1.0f;
				energy -= 10;
				GLfloat tmpAngle = 0;
				glm::vec3 color = glm::vec3(0.0f, 0.0f, 1.0f);
				gameObject::gameState()->spawnBullet(gameObject::gameState()->playerBullets, tmpAngle, color, glm::vec2(position.x + radius * cos(tmpAngle + CORRECTION), position.y + radius * sin(tmpAngle + CORRECTION)), radius / 10.0f, glm::vec2(bSpeed * cos(tmpAngle + CORRECTION), bSpeed * sin(tmpAngle + CORRECTION)));
				tmpAngle = 2 * PI / 4;
				gameObject::gameState()->spawnBullet(gameObject::gameState()->playerBullets, tmpAngle, color, glm::vec2(position.x + radius * cos(tmpAngle + CORRECTION), position.y + radius * sin(tmpAngle + CORRECTION)), radius / 10.0f, glm::vec2(bSpeed * cos(tmpAngle + CORRECTION), bSpeed * sin(tmpAngle + CORRECTION)));
				tmpAngle = 4 * PI / 4;
				gameObject::gameState()->spawnBullet(gameObject::gameState()->playerBullets, tmpAngle, color, glm::vec2(position.x + radius * cos(tmpAngle + CORRECTION), position.y + radius * sin(tmpAngle + CORRECTION)), radius / 10.0f, glm::vec2(bSpeed * cos(tmpAngle + CORRECTION), bSpeed * sin(tmpAngle + CORRECTION)));
				tmpAngle = 6 * PI / 4;
				gameObject::gameState()->spawnBullet(gameObject::gameState()->playerBullets, tmpAngle, color, glm::vec2(position.x + radius * cos(tmpAngle + CORRECTION), position.y + radius * sin(tmpAngle + CORRECTION)), radius / 10.0f, glm::vec2(bSpeed * cos(tmpAngle + CORRECTION), bSpeed * sin(tmpAngle + CORRECTION)));

			}
			else;
		else
		{
			if (energy >= 10 && shotDelay[1] <= 0.0f)
			{
				shotDelay[1] = 1.0f;
				energy -= 10;
				GLfloat tmpAngle = 0;
				glm::vec3 color = glm::vec3(0.0f, 0.0f, 1.0f);
				gameObject::gameState()->spawnBullet(gameObject::gameState()->playerBullets, tmpAngle, color, glm::vec2(position.x + radius * cos(tmpAngle + CORRECTION), position.y + radius * sin(tmpAngle + CORRECTION)), radius / 10.0f, glm::vec2(bSpeed * cos(tmpAngle + CORRECTION), bSpeed * sin(tmpAngle + CORRECTION)));
				tmpAngle = 2 * PI / 4;
				gameObject::gameState()->spawnBullet(gameObject::gameState()->playerBullets, tmpAngle, color, glm::vec2(position.x + radius * cos(tmpAngle + CORRECTION), position.y + radius * sin(tmpAngle + CORRECTION)), radius / 10.0f, glm::vec2(bSpeed * cos(tmpAngle + CORRECTION), bSpeed * sin(tmpAngle + CORRECTION)));
				tmpAngle = 4 * PI / 4;
				gameObject::gameState()->spawnBullet(gameObject::gameState()->playerBullets, tmpAngle, color, glm::vec2(position.x + radius * cos(tmpAngle + CORRECTION), position.y + radius * sin(tmpAngle + CORRECTION)), radius / 10.0f, glm::vec2(bSpeed * cos(tmpAngle + CORRECTION), bSpeed * sin(tmpAngle + CORRECTION)));
				tmpAngle = 6 * PI / 4;
				gameObject::gameState()->spawnBullet(gameObject::gameState()->playerBullets, tmpAngle, color, glm::vec2(position.x + radius * cos(tmpAngle + CORRECTION), position.y + radius * sin(tmpAngle + CORRECTION)), radius / 10.0f, glm::vec2(bSpeed * cos(tmpAngle + CORRECTION), bSpeed * sin(tmpAngle + CORRECTION)));
			}
		}
	energy += 10 * dt;
	if (energy > 100)
		energy = 100;	
	if (damageTimer > 0.0f)
		damageTimer -= dt;
	Shield.color = glm::vec3(1.0f);
}

void Player::draw(spriteRenderer & renderer)
{
	renderer.drawSprite(this->texture, this->position - this->radius, glm::vec2(this->radius) * 2.0f, this->rotation, this->color);
	if(energy >= 20.0f)
		Shield.draw(renderer);
	float padding = 10.0f;
	glm::vec3 colorTmp = glm::vec3(0.5f, 0.0f, 0.0f);
	glm::vec2 pos = glm::vec2(padding, gameObject::gameState()->height - (padding + 10.0f));
	renderer.drawSprite(this->bars, pos, glm::vec2(150.0f, 10.0f), 0.0f, colorTmp);
	colorTmp = glm::vec3(1.0f, 0.0f, 0.0f);
	renderer.drawSprite(this->bars, pos + 1.0f, glm::vec2(150.0f * health / 100.0f, 8.0f), 0.0f, colorTmp);
	colorTmp = glm::vec3(0.0f, 0.0f, 0.5f);
	pos = glm::vec2(gameObject::gameState()->width - (padding + 150.0f), gameObject::gameState()->height - (padding + 10.0f));
	renderer.drawSprite(this->bars, pos, glm::vec2(150.0f, 10.0f), 0.0f, colorTmp);
	colorTmp = glm::vec3(0.0f, 0.0f, 1.0f);
	renderer.drawSprite(this->bars, pos + 1.0f, glm::vec2(150.0f * energy / 100.0f, 8.0f), 0.0f, colorTmp);
	
	if(damageTimer <= 0.0f)
		color = glm::vec3(1.0f, 1.0f, 1.0f);
}


void Player::init()
{
	this->position = glm::vec2(gameObject::gameState()->width / 2, gameObject::gameState()->height / 2);
	Shield.color = glm::vec3(1.0f, 1.0f, 1.0f);
	Shield.rotation = 0.0f;
	this->health = 100.0f;
	this->energy = 100.0f;
	this->rotation = 0.0f;
}

