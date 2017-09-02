#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

class Entity : public sf::Drawable
{
public:
	Entity();
	Entity(sf::Vector2f& position, sf::Vector2f& velocity);
	~Entity();

	void reset();
	void update();

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	virtual void render(sf::RenderTarget& target);
	sf::Vector2f mPosition;
	//sf::Vector2f mAccelleration;
	sf::Vector2f mVelocity;

	sf::CircleShape mSprite;
};