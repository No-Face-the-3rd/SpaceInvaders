#include "Game.h"

#include "Resource Manager.h"
#include "Sprite Renderer.h"

spriteRenderer *renderer;

Game::Game(GLuint widthIn, GLuint heightIn) :gs(INIT),keys(),keysProcessed(), width(widthIn), height(heightIn)
{
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

	ResourceManager::loadTexture("Textures/Brick_Wall.jpg", GL_TRUE, "brick_wall");
	
	renderer = new spriteRenderer(ResourceManager::getShader("sprite"));
}

void Game::processInput(GLfloat dt)
{
}

void Game::update(GLfloat dt)
{
}

void Game::render()
{
	renderer->drawSprite(ResourceManager::getTexture("brick_wall"), glm::vec2(0, 0), glm::vec2(800, 600), 0.0f, glm::vec3(0.25f, 0.25f, 0.25f));
}
