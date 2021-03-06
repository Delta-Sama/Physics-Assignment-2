#include "Box.h"
#include "TextureManager.h"

Box::Box()
{
	TextureManager::Instance()->load("../Assets/sprites/Lootbox.png", "lootbox");

	setWidth(25);
	setHeight(25);

	getTransform()->position = glm::vec2(0.0f, 0.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PLANE);
}

Box::~Box()
= default;

void Box::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;
	const float ang = getTransform()->rotation.x;
	
	TextureManager::Instance()->draw("lootbox", x, y, ang, 255, true, SDL_FLIP_NONE, { getWidth(),getHeight() });
}

void Box::update()
{

}

void Box::clean()
{

}