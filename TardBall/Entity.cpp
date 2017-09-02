#include "Entity.h"
#include <SFML/Graphics/RenderWindow.hpp>

Entity::Entity()
{
}

Entity::Entity(sf::Vector2f & position, sf::Vector2f & velocity)
	: mPosition(position), mVelocity(velocity)
{
	mSprite.setRadius(15.0f);
	mSprite.setFillColor(sf::Color::Red);
}

Entity::~Entity()
{
}

void Entity::reset()
{
}

void Entity::update()
{
	mPosition += mVelocity;
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
	printf("%f",mPosition.x);
}
