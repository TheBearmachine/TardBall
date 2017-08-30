#include "Simulation.h"
#include <SFML/Window/Event.hpp>

Simulation::Simulation() :
	window(sf::VideoMode(640, 480), sf::String("Ball Sim"))
{

}

Simulation::~Simulation()
{
}

void Simulation::run()
{
	ball = Entity(initialPosition, initialVelocity);
	GUIText.setString("A/D - X Velocity = " + std::to_string(initialVelocity.x) + ", W/S - Y Velocity = " + std::to_string(initialVelocity.y)
					  + "\nR/F - Elasticity = " + std::to_string(elasticity));
	GUIText.setPosition(32, window.getSize().y);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();

				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::A)
				{

				}

				GUIText.setString("A/D - X Velocity = " + std::to_string(initialVelocity.x) + ", W/S - Y Velocity = " + std::to_string(initialVelocity.y)
								  + "\nR/F - Elasticity = " + std::to_string(elasticity));

				break;

			default:
				break;
			}

			update();
			window.clear();
			render(window);
			window.display();
		}

	}
}

void Simulation::update()
{
	if (!simulate)
		return;



	ball.update(deltaTime);


}

void Simulation::physics()
{
	ball.mVelocity = sf::Vector2f(ball.mVelocity.x, ball.mVelocity.y + gravity);

	if (ball.mPosition.y >= window.getSize().y && ball.mVelocity.y < 0)
	{
		ball.mVelocity.y *= -elasticity;
		if (ball.mVelocity.y >= -0.1f && ball.mVelocity.y <= 0.1f)
			ball.mVelocity.y = 0;
	}

	if (ball.mPosition.x >= window.getSize().x || ball.mPosition.x <= 0)
	{
		ball.mVelocity.x *= -elasticity;
		if (ball.mVelocity.x >= -0.1f && ball.mVelocity.x <= 0.1f)
			ball.mVelocity.x = 0;
	}
}

void Simulation::render(sf::RenderWindow &win)
{
	win.draw(ball);
	win.draw(GUIText);
}
