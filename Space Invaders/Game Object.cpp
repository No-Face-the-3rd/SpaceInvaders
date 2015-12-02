#include "Game Object.h"



gameObject::gameObject() : position(0,0),speed(0.0f),color(1.0f),radius(1),rotation(0.0f),texture()
{
}

gameObject::gameObject(glm::vec2 pos, GLfloat rad, Texture2D tex, glm::vec3 colorIn, glm::vec2 spd, GLfloat angle) : position(pos),speed(spd),color(colorIn),radius(rad),rotation(0.0f),texture(tex)
{
}


gameObject::~gameObject()
{
}

void gameObject::draw(spriteRenderer & renderer)
{
	renderer.drawSprite(this->texture, this->position - this->radius, glm::vec2(this->radius) * 2.0f, this->rotation, this->color);
}

void gameObject::update(GLfloat dt)
{
	position = position + speed * dt;
}