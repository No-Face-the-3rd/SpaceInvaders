#include "Game.h"

#include "Resource Manager.h"
#include "Sprite Renderer.h"

#include <algorithm>
#include <iostream>
#include <time.h>
#include <glm/gtc/random.hpp>

#define PI 3.1415926535f


spriteRenderer *renderer;

Game::Game()
{
	gameObject::gameState() = this;
}

Game::Game(GLuint widthIn, GLuint heightIn) :gs(SPLASH), keys(), keysProcessed(), mouse(), mouseProcessed(), width(widthIn), height(heightIn), enemyAmt(3), playerKills(0), mousePos(0.0, 0.0), killAfterChange(0)
{
	gameObject::gameState() = this;
}

Game::~Game()
{
	delete renderer;
}

void Game::init()
{
	ResourceManager::loadShader("Shaders/sprite.vs", "Shaders/sprite.frag", nullptr, "sprite");

	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->width), static_cast<GLfloat>(this->height), 0.0f, -1.0f, 1.0f);
	ResourceManager::getShader("sprite").use().setInteger("image", 0);
	ResourceManager::getShader("sprite").setMatrix4("projection", projection);

	ResourceManager::loadTexture("Textures/Game_Background.jpg", GL_FALSE, "gamebackground");
	ResourceManager::loadTexture("Textures/Ship.png", GL_TRUE, "ship");
	ResourceManager::loadTexture("Textures/Shield.png", GL_TRUE, "shield");
	ResourceManager::loadTexture("Textures/Bullet.png", GL_TRUE, "bullet");
	ResourceManager::loadTexture("Textures/Enemy.png", GL_TRUE, "enemy");
	ResourceManager::loadTexture("Textures/Bar.png", GL_TRUE, "bar");
	
	renderer = new spriteRenderer(ResourceManager::getShader("sprite"));
	player.texture = ResourceManager::getTexture("ship");
	player.Shield.texture = ResourceManager::getTexture("shield");
	player.position = glm::vec2(width / 2.0f, height / 2.0f);
	player.bars = ResourceManager::getTexture("bar");

	srand(time(NULL));
}

void Game::processInput(GLfloat dt)
{
	for (int i = 0; i < 1024; ++i)
	{
		if (keys[i] && !keysProcessed[i])
		{
			keysProcessed[i] = GL_TRUE;
			continue;
		}
		if (!keys[i] && keysProcessed[i])
		{
			keysProcessed[i] = GL_FALSE;
		}
	}
	for (int i = 0; i < 3; ++i)
	{
		if (mouse[i] && !mouseProcessed[i])
		{
			mouseProcessed[i] = GL_TRUE;
			continue;
		}
	}
}

void Game::update(GLfloat dt)
{
	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
		if (player.position.x > player.radius)
			player.position.x = player.position.x - player.speed.x * dt;
	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
		if (player.position.x < width - player.radius)
			player.position.x = player.position.x + player.speed.x * dt;
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
		if (player.position.y > player.radius)
			player.position.y = player.position.y - player.speed.y * dt;
	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
		if (player.position.y < height - player.radius)
			player.position.y = player.position.y + player.speed.y * dt;
	player.update(dt);
	for (int i = 0; i < playerBullets.size();++i)
	{
		playerBullets[i].update(dt);
		if (playerBullets[i].position.x < 0 || playerBullets[i].position.y < 0 || playerBullets[i].position.x > width || playerBullets[i].position.y > height)
		{
			pBulletDelete.emplace_back(i);
		}
	}
	std::sort(pBulletDelete.begin(), pBulletDelete.end());
	for (int i = 0; i < pBulletDelete.size(); ++i)
	{
		if (pBulletDelete[i] >= playerBullets.size() - 1)
		{
			playerBullets.pop_back();
			continue;
		}
		playerBullets.erase(playerBullets.begin() + pBulletDelete[i] - i);
	}
	pBulletDelete.clear();
	if (killAfterChange >= enemyAmt)
	{
		++enemyAmt;
		killAfterChange = 0;
	}
	if (enemies.size() < enemyAmt)
	{
		spawnEnemy();
	}
	for (int i = 0; i < enemies.size();++i)
	{
		enemies[i].update(dt);
	}
	if (keys[GLFW_KEY_SPACE] && !keysProcessed[GLFW_KEY_SPACE])
		++enemyAmt;
	int popped = 0;
	for (int i = 0; i < enemies.size(); ++i)
	{
		if (enemies[i].dead)
		{
			enemies[i].color = glm::vec3(1.0f, 0.0f, 0.0f);
			if (enemies[i].aiTimer <= 0.0f)
			{
				enemies[i].color = glm::vec3(1.0f, 1.0f, 1.0f);
				if (i >= enemies.size())
					enemies.pop_back();
				else
					enemies.erase(enemies.begin() + i - popped);
				++playerKills;
				++killAfterChange;
				++popped;
			}
		}
	}
	popped = 0;

	if (player.health <= 0.0f);

	player.health += 3.5f * dt;
	if (player.health > 100.0f)
		player.health = 100.0f;
	else if (player.health < 0.0f)
		player.health = 0.0f;
}

void Game::render()
{
	renderer->drawSprite(ResourceManager::getTexture("gamebackground"), glm::vec2(0, 0), glm::vec2(this->width, height), 0.0f);
	for (auto iter : enemies)
		iter.draw(*renderer);
	player.draw(*renderer);
	for(auto iter:playerBullets)
		iter.draw(*renderer);
}

void Game::enterGame()
{

}

void Game::spawnBullet(std::vector<gameObject> &bullets, GLfloat angle, glm::vec3 colorIn, glm::vec2 pos, GLfloat radius, glm::vec2 spd)
{
	bullets.emplace_back(gameObject(pos, radius, ResourceManager::getTexture("bullet"), colorIn, spd, angle));
}

void Game::spawnEnemy()
{
	
	enemies.emplace_back();
	Enemy *tmp = &enemies[enemies.size() - 1];
	tmp->texture = ResourceManager::getTexture("enemy");
	tmp->aiTimer = 1.0f;
	tmp->color = glm::vec3(1.0f, 1.0f, 1.0f);
	tmp->dead = false;
	tmp->position = glm::vec2(glm::linearRand(0.0f,(float)width), glm::linearRand(0.0f,(float)height));
	if (std::abs(tmp->position.y - player.position.y) < 50)
		tmp->position.x = std::abs(tmp->position.x - player.position.x) > 50 ? tmp->position.x : (tmp->position.x < player.position.x) ? tmp->position.x - 50 : tmp->position.x + 50;
	if (std::abs(tmp->position.x - player.position.x) < 50)
		tmp->position.y = std::abs(tmp->position.y - player.position.y) > 50 ? tmp->position.y : (tmp->position.y < player.position.y) ? tmp->position.y - 50 : tmp->position.y + 50;
	tmp->radius = 20.0f;
	tmp->rotation = glm::linearRand(0.0f, 2 * PI);
	tmp->speed = glm::vec2(75.0f, 75.0f);
	tmp->targetLoc = tmp->position;
	tmp->clockwise = std::rand() % 2;
}