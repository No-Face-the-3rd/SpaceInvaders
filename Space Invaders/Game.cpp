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

Game::Game(GLuint widthIn, GLuint heightIn) :gs(SPLASH), keys(), keysProcessed(), mouse(), mouseProcessed(), width(widthIn), height(heightIn), enemyAmt(3), playerKills(0), mousePos(0.0, 0.0), killAfterChange(0), playerMaxHP(100.0f), playerMaxEnergy(100.0f) , staticVisuals(), buttons(), anyKeyDelay(0), shouldClose(GL_FALSE)
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
	ResourceManager::loadTexture("Textures/Loss.png", GL_TRUE, "loss");
	ResourceManager::loadTexture("Textures/Title.png", GL_TRUE, "title");
	ResourceManager::loadTexture("Textures/Play.png", GL_TRUE, "play");
	ResourceManager::loadTexture("Textures/Resume.png", GL_TRUE, "resume");
	ResourceManager::loadTexture("Textures/Menu.png", GL_TRUE, "menu");
	ResourceManager::loadTexture("Textures/Exit.png", GL_TRUE, "exit");
	ResourceManager::loadTexture("Textures/Button.png", GL_TRUE, "button");
	ResourceManager::loadTexture("Textures/Pause.png", GL_TRUE, "pause");
	
	renderer = new spriteRenderer(ResourceManager::getShader("sprite"));
	player.texture = ResourceManager::getTexture("ship");
	player.Shield.texture = ResourceManager::getTexture("shield");
	player.position = glm::vec2(width / 2.0f, height / 2.0f);
	player.bars = ResourceManager::getTexture("bar");
	staticVisuals[0].texture = ResourceManager::getTexture("loss");
	staticVisuals[1].texture = ResourceManager::getTexture("title");
	staticVisuals[2].texture = ResourceManager::getTexture("title");
	staticVisuals[3].texture = ResourceManager::getTexture("play");
	staticVisuals[4].texture = ResourceManager::getTexture("exit");
	staticVisuals[5].texture = ResourceManager::getTexture("resume");
	staticVisuals[6].texture = ResourceManager::getTexture("menu");
	staticVisuals[7].texture = ResourceManager::getTexture("pause");

	for (int i = 0; i < 3; ++i)
	{
		buttons[i].texture = ResourceManager::getTexture("button");
		buttons[i].color = glm::vec3(0.5f, 0.5f, 1.0f);
	}


	glm::vec2 mid = glm::vec2(width / 2.0f, height / 2.0f);

	for (int i = 0; i < 3; ++i)
		staticVisuals[i].color = glm::vec3(1.0f, 1.0f, 0.0f);
	staticVisuals[7].color = glm::vec3(1.0f, 1.0f, 0.0f);
	staticVisuals[0].radius = mid.x / 4.0f;
	staticVisuals[0].position = glm::vec2(mid.x, mid.y);
	staticVisuals[1].radius = staticVisuals[7].radius = mid.x / 4.0f;
	staticVisuals[1].position = staticVisuals[7].position = glm::vec2(mid.x, staticVisuals[1].radius / 2.0f);
	staticVisuals[2].radius = mid.x / 2.0f;
	staticVisuals[2].position = glm::vec2(mid.x, mid.y);
	buttons[0].radius = staticVisuals[3].radius = staticVisuals[5].radius = mid.x / 4.0f;
	buttons[0].position = staticVisuals[3].position = staticVisuals[5].position = glm::vec2(mid.x, mid.y / 2.0f);
	buttons[1].radius = staticVisuals[6].radius = mid.x / 4.0f;
	buttons[1].position = staticVisuals[6].position = glm::vec2(mid.x, mid.y);
	buttons[2].radius = staticVisuals[4].radius = mid.x / 4.0f;
	buttons[2].position = staticVisuals[4].position = glm::vec2(mid.x, mid.y + mid.y / 2.0f);
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
	switch (gs)
	{
	case SPLASH:
		for (int i = 0; i < 3; ++i)
			if (mouse[i])
			{
				gs = MENU_INIT;
				break;
			}
		for (int i = 0; i < 1023; ++i)
			if (keys[i])
			{
				gs = MENU_INIT;
				break;
			}
		break;
	case MENU_INIT:
		gs = MENU;
		break;
	case MENU:
		for (int i = 0; i < 3; ++i)
		{
			if (mousePos.x <= buttons[i].position.x + buttons[i].radius && mousePos.x >= buttons[i].position.x - buttons[i].radius && mousePos.y <= buttons[i].position.y + buttons[i].radius / 4.0f && mousePos.y >= buttons[i].position.y - buttons[i].radius / 4.0f)
				buttons[i].color = glm::vec3(1.0f, 0.5f, 1.0f);
			else
				buttons[i].color = glm::vec3(0.5f, 0.5f, 1.0f);
		}
		if (mouse[GLFW_MOUSE_BUTTON_LEFT] && !mouseProcessed[GLFW_MOUSE_BUTTON_LEFT])
		{
			if (mousePos.x <= buttons[0].position.x + buttons[0].radius && mousePos.x >= buttons[0].position.x - buttons[0].radius && mousePos.y <= buttons[0].position.y + buttons[0].radius / 4.0f && mousePos.y >= buttons[0].position.y - buttons[0].radius / 4.0f)
				gs = PLAY_INIT;
			if (mousePos.x <= buttons[2].position.x + buttons[2].radius && mousePos.x >= buttons[2].position.x - buttons[2].radius && mousePos.y <= buttons[2].position.y + buttons[2].radius / 4.0f && mousePos.y >= buttons[2].position.y - buttons[2].radius / 4.0f)
				shouldClose = GL_TRUE;
		}
		if(keys[GLFW_KEY_X])
			shouldClose = GL_TRUE;
		if (keys[GLFW_KEY_P] && !keysProcessed[GLFW_KEY_P])
			gs = PLAY_INIT;
		break;
	case PLAY_INIT:
		enterGame();
		break;
	case PLAY:
	{
		if ((keys[GLFW_KEY_P] && !keysProcessed[GLFW_KEY_P]) || (keys[GLFW_KEY_ESCAPE] && !keysProcessed[GLFW_KEY_ESCAPE]))
			gs = PAUSE;
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
		for (int i = 0; i < playerBullets.size(); ++i)
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
			else if (playerBullets.size() <= 0)
				break;
			playerBullets.erase(playerBullets.begin() + pBulletDelete[i] - i);
		}
		pBulletDelete.clear();
		if (killAfterChange >= enemyAmt)
		{
			++enemyAmt;
			killAfterChange = 0;
			playerMaxHP += enemyAmt / 2.0f;
			playerMaxEnergy += enemyAmt / 2.0f;
		}
		for (int i = 0; i < enemyBullets.size(); ++i)
		{
			enemyBullets[i].update(dt);
			if (enemyBullets[i].position.x < 0 || enemyBullets[i].position.y < 0 || enemyBullets[i].position.x > width || enemyBullets[i].position.y > height)
			{

				eBulletDelete.emplace_back(i);
			}
		}
		std::sort(eBulletDelete.begin(), eBulletDelete.end());
		for (int i = 0; i < eBulletDelete.size(); ++i)
		{
			if (eBulletDelete[i] >= enemyBullets.size() - 1)
			{
				enemyBullets.pop_back();
				continue;
			}
			else if (enemyBullets.size() <= 0)
				break;
			enemyBullets.erase(enemyBullets.begin() + eBulletDelete[i] - i);
		}
		eBulletDelete.clear();

		if (enemies.size() < enemyAmt)
		{
			spawnEnemy();
		}
		for (int i = 0; i < enemies.size(); ++i)
		{
			enemies[i].update(dt);
		}
		//if (keys[GLFW_KEY_SPACE]) && !keysProcessed[GLFW_KEY_SPACE])
			//++enemyAmt;
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
		player.health += 2.5f / 100.0f * playerMaxHP * dt;
		if (player.health > playerMaxHP)
			player.health = playerMaxHP;
		else if (player.health <= 0.0f)
		{
			player.health = 0.0f;
			anyKeyDelay = 0;
			gs = LOSE;
		}
		break;
	}
	case PAUSE:
	{
		glm::vec2 mid = glm::vec2(width / 2.0f, height / 2.0f);
		for (int i = 0; i < 3; ++i)
		{
			if (mousePos.x <= buttons[i].position.x + buttons[i].radius && mousePos.x >= buttons[i].position.x - buttons[i].radius && mousePos.y <= buttons[i].position.y + buttons[i].radius / 4.0f && mousePos.y >= buttons[i].position.y - buttons[i].radius / 4.0f)
				buttons[i].color = glm::vec3(1.0f, 0.5f, 1.0f);
			else
				buttons[i].color = glm::vec3(0.5f, 0.5f, 1.0f);
		}
		if (mouse[GLFW_MOUSE_BUTTON_LEFT] && !mouseProcessed[GLFW_MOUSE_BUTTON_LEFT])
		{
			if (mousePos.x <= buttons[0].position.x + buttons[0].radius && mousePos.x >= buttons[0].position.x - buttons[0].radius && mousePos.y <= buttons[0].position.y + buttons[0].radius / 4.0f && mousePos.y >= buttons[0].position.y - buttons[0].radius / 4.0f)
				gs = PLAY;
			if (mousePos.x <= buttons[1].position.x + buttons[1].radius && mousePos.x >= buttons[1].position.x - buttons[1].radius && mousePos.y <= buttons[1].position.y + buttons[1].radius / 4.0f && mousePos.y >= buttons[1].position.y - buttons[1].radius / 4.0f)
				gs = MENU_INIT;
			if (mousePos.x <= buttons[2].position.x + buttons[2].radius && mousePos.x >= buttons[2].position.x - buttons[2].radius && mousePos.y <= buttons[2].position.y + buttons[2].radius / 4.0f && mousePos.y >= buttons[2].position.y - buttons[2].radius / 4.0f)
				shouldClose = GL_TRUE;
		}
		if (keys[GLFW_KEY_X])
			shouldClose = GL_TRUE;
		if (keys[GLFW_KEY_M])
			gs = MENU_INIT;
		if ((keys[GLFW_KEY_ESCAPE] && !keysProcessed[GLFW_KEY_ESCAPE]) || (keys[GLFW_KEY_R] && !keysProcessed[GLFW_KEY_R]))
			gs = PLAY;
		break;
	}
	case LOSE:
		if (anyKeyDelay > 100)
		{
			for (int i = 0; i < 3; ++i)
				if (mouse[i])
				{
					gs = MENU_INIT;
					break;
				}
			for (int i = 0; i < 1023; ++i)
				if (keys[i])
				{
					gs = MENU_INIT;
					break;
				}
		}
		++anyKeyDelay;
		break;
	}
}

void Game::render()
{
	renderer->drawSprite(ResourceManager::getTexture("gamebackground"), glm::vec2(0, 0), glm::vec2(this->width, height), 0.0f);
	switch (gs)
	{
	case SPLASH:
		staticVisuals[2].draw(*renderer);
		break;
	case MENU:
		staticVisuals[1].draw(*renderer);
		buttons[0].draw(*renderer);
		buttons[2].draw(*renderer);
		staticVisuals[3].draw(*renderer);
		staticVisuals[4].draw(*renderer);
		break;
	case PLAY:
		for (auto iter : enemies)
			iter.draw(*renderer);
		player.draw(*renderer);
		for(auto iter:playerBullets)
			iter.draw(*renderer);
		for (auto iter : enemyBullets)
			iter.draw(*renderer);
		break;
	case PAUSE:
		buttons[0].draw(*renderer);
		buttons[1].draw(*renderer);
		buttons[2].draw(*renderer);
		staticVisuals[4].draw(*renderer);
		staticVisuals[5].draw(*renderer);
		staticVisuals[6].draw(*renderer);
		staticVisuals[7].draw(*renderer);
		break;
	case LOSE:
		for (auto iter : enemies)
			iter.draw(*renderer);
		player.draw(*renderer);
		for (auto iter : playerBullets)
			iter.draw(*renderer);
		for (auto iter : enemyBullets)
			iter.draw(*renderer);
		staticVisuals[0].draw(*renderer);
		break;
	}
}

void Game::enterGame()
{
	gs = PLAY;
	enemies.clear();
	enemyAmt = 3;
	playerKills = 0;
	killAfterChange = 0;
	playerMaxHP = 100.0f;
	playerMaxEnergy = 100.0f;
	playerBullets.clear();
	enemyBullets.clear();
	pBulletDelete.clear();
	eBulletDelete.clear();
	eDelete.clear();
	player.init();
	anyKeyDelay = 0;
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
	if (std::rand() % 2)
		tmp->clockwise = true;
	else
		tmp->clockwise = false;
}