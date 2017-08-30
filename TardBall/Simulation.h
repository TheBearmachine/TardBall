#pragma once
#include "Entity.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
class Simulation
{
public:
	Simulation();
	~Simulation();

	void run();
	void update();
	void render(sf::RenderWindow &win);

	float gravity;
	float friction;
	float airResistance;
	float elasticity;

	float deltaTime;

	bool simulate;

	sf::Vector2f initialVelocity;
	sf::Vector2f initialPosition;
	Entity ball;
	sf::RenderWindow window;
	sf::Text GUIText;

private:
	void physics();
};