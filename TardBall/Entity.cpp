#include "Entity.h"
#include <SFML/Graphics/RenderWindow.hpp>

Entity::Entity()
{
}

Entity::Entity(sf::Vector2f & position, sf::Vector2f & velocity)
	: mPosition(position), mVelocity(velocity)
{
}

Entity::~Entity()
{
}

void Entity::reset()
{
}

void Entity::update(const float & deltaTime)
{
	mPosition += mVelocity * deltaTime;
	mSprite.setPosition(mPosition);
}

void Entity::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= mSprite.getTransform();
	target.draw(mSprite, states);
}

void Entity::render(sf::RenderTarget& target)
{
	target.draw(mSprite);
}
