#include "Game.h"

#include "Resource Manager.h"
#include "Sprite Renderer.h"

#include <algorithm>
#include <iostream>


spriteRenderer *renderer;

Game::Game()
{
	gameObject::gameState() = this;
}

Game::Game(GLuint widthIn, GLuint heightIn) :gs(SPLASH),keys(),keysProcessed(),mouse(),mouseProcessed(), width(widthIn), height(heightIn), enemyAmt(0), playerKills(0), mousePos(0.0,0.0)
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
	
	renderer = new spriteRenderer(ResourceManager::getShader("sprite"));
	player.texture = ResourceManager::getTexture("ship");
	player.Shield.texture = ResourceManager::getTexture("shield");
	player.position = glm::vec2(width / 2.0f, height / 2.0f);
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
}

void Game::render()
{
	renderer->drawSprite(ResourceManager::getTexture("gamebackground"), glm::vec2(0, 0), glm::vec2(this->width, height), 0.0f);
	player.draw(*renderer);
	for(auto iter:playerBullets)
		iter.draw(*renderer);
}

void Game::enterGame()
{

}

void Game::SpawnBullet(std::vector<gameObject> &bullets, GLfloat angle, glm::vec3 colorIn, glm::vec2 pos, GLfloat radius, glm::vec2 spd)
{
	bullets.emplace_back(gameObject(pos, radius, ResourceManager::getTexture("bullet"), colorIn, spd, angle));
}
