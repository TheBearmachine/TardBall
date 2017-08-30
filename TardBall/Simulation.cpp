#include "Simulation.h"
#include <SFML/Window/Event.hpp>

static const char* FONT_EH = "Fonts/sui_generis_rg.ttf";

Simulation::Simulation() :
	window(sf::VideoMode(640, 480), sf::String("Ball Sim"))
{
	currentBox = nullptr;
	positionBox = new TextBox(0, 0, 60, 5, "Position");
	velocityBox = new TextBox(80, 0, 60, 5, "Velocity");
	elasticityBox = new TextBox(160, 0, 60, 5, "Elasticity");
	gravityBox = new TextBox(240, 0, 60, 5, "Gravity");
	
	textBoxes = std::vector<TextBox*>();

	textBoxes.push_back(positionBox);
	textBoxes.push_back(velocityBox);
	textBoxes.push_back(elasticityBox);
	textBoxes.push_back(gravityBox);

	
}

Simulation::~Simulation()
{
}

void Simulation::updateGUIText()
{
	GUIText.setString("A/D - X Velocity = " + std::to_string(initialVelocity.x) + ", W/S - Y Velocity = " + std::to_string(initialVelocity.y)
					  + "\nLeft/Right/Up/Down - Initial Position \nR/F - Elasticity = " + std::to_string(elasticity)
					  + "\nT/G - Gravity = " + std::to_string(gravity)
					  + "\n Space - Simulate/Reset");

}

void Simulation::run()
{
	initialPosition.x = window.getSize().x / 2.0f;
	initialPosition.y = window.getSize().y / 2.0f;

	gravity = 9.82f;
	friction = 0.3f;
	elasticity = 0.5f;
	simulate = false;
	deltaTime = 1.0f / 60.0f;

	ball = Entity(initialPosition, initialVelocity);
	updateGUIText();
	defaultFont.loadFromFile(FONT_EH);
	GUIText.setFont(defaultFont);
	GUIText.setCharacterSize(16);
	GUIText.setPosition(32, window.getSize().y / 10.0f);
	GUIText.setFillColor(sf::Color::Green);
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
			case sf::Event::TextEntered:
				if (currentBox)
					currentBox->handleInput(event);
				break;
			case sf::Event::MouseButtonPressed:
				gui(event.mouseButton.x, event.mouseButton.y);
				break;
#pragma region keyevents
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					window.close();
					break;

				case sf::Keyboard::A:
					initialVelocity.x -= 0.1f;
					initialVelocity.x = std::max(-4.0f, initialVelocity.x);
					break;

				case sf::Keyboard::D:
					initialVelocity.x += 0.1f;
					initialVelocity.x = std::min(4.0f, initialVelocity.x);
					break;

				case sf::Keyboard::W:
					initialVelocity.y -= 0.1f;
					initialVelocity.y = std::max(-4.0f, initialVelocity.y);
					break;

				case sf::Keyboard::S:
					initialVelocity.y += 0.1f;
					initialVelocity.y = std::min(4.0f, initialVelocity.y);
					break;

				case sf::Keyboard::Left:
					initialPosition.x -= 1.0f;
					initialPosition.x = std::max(0.0f, initialPosition.x);
					break;

				case sf::Keyboard::Right:
					initialPosition.x += 1.0f;
					initialPosition.x = std::min((float)window.getSize().x, initialPosition.x);
					break;

				case sf::Keyboard::Up:
					initialPosition.y -= 1.0f;
					initialPosition.y = std::max(0.0f, initialPosition.y);
					break;

				case sf::Keyboard::Down:
					initialPosition.y += 1.0f;
					initialPosition.y = std::min((float)window.getSize().y, initialPosition.y);
					break;

				case sf::Keyboard::R:
					elasticity += 0.1f;
					elasticity = std::min(elasticity, 1.0f);
					break;

				case sf::Keyboard::F:
					elasticity -= 0.1f;
					elasticity = std::max(elasticity, 0.0f);
					break;


				case sf::Keyboard::T:
					gravity += 0.01f;
					gravity = std::min(gravity, 15.0f);
					break;

				case sf::Keyboard::G:
					gravity -= 0.01f;
					gravity = std::max(gravity, 0.5f);
					break;

				case sf::Keyboard::Space:
					if (simulate = true)
						reset();
					simulate = !simulate;
					break;
				}
				updateGUIText();

				break;
#pragma endregion

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
	{
		ball.mPosition = initialPosition;
		ball.update(deltaTime);
		return;
	}

	physics();
	ball.update(deltaTime);
}

void Simulation::gui(int x, int y)
{
	//SORRY

	if (currentBox)
		currentBox->deselect();

	currentBox = nullptr;

	if (positionBox->isClicked(x, y))
		currentBox = positionBox;

	if (velocityBox->isClicked(x, y))
		currentBox = velocityBox;

	if (elasticityBox->isClicked(x, y))
		currentBox = elasticityBox;

	if (gravityBox->isClicked(x, y))
		currentBox = gravityBox;

	if (currentBox)
		currentBox->select();
}

void Simulation::physics()
{
	ball.mVelocity.y += gravity;

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

void Simulation::reset()
{
	ball.mPosition = initialPosition;
	ball.mVelocity = sf::Vector2f();
}

void Simulation::render(sf::RenderWindow &win)
{
	ball.render(win);

	for (auto box : textBoxes)
		box->render(&win);

	win.draw(GUIText);
}
