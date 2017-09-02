#include "Simulation.h"
#include <SFML/Window/Event.hpp>
#include <chrono>
#include <thread>
#include "Vector.h"

static const char* FONT_EH = "Fonts/sui_generis_rg.ttf";

Simulation::Simulation() :
	window(sf::VideoMode(640, 480), sf::String("Ball Sim"))
{
	currentBox = nullptr;

	gravity = 9.82f;
	friction = 0.3f;
	elasticity = 0.5f;
	simulate = false;
	fps = 60;
	deltaTime = 1.0f / (float)fps;
	floorHeight = window.getSize().y;

	textBoxes = std::vector<TextBox*>();
	textBoxes.push_back(new TextBox(0, 10, 100, 3, "VelocityX", &initialVelocity.x, "0"));
	textBoxes.push_back(new TextBox(120, 10, 100, 3, "VelocityY", &initialVelocity.y, "0"));
	textBoxes.push_back(new TextBox(240, 10, 100, 3, "Elasticity", &elasticity, "0.5"));
	textBoxes.push_back(new TextBox(360, 10, 100, 3, "Gravity", &gravity, "9.82"));
	textBoxes.push_back(new TextBox(480, 10, 100, 3, "Friction", &friction, "1.0"));


}

Simulation::~Simulation()
{
}

void Simulation::updateGUIText()
{
	GUIText.setString("\nLeft/Right/Up/Down - Initial Position \nSpace - Simulate/Reset");

}

void Simulation::initializeGUI()
{
	updateGUIText();
	defaultFont.loadFromFile(FONT_EH);
	GUIText.setFont(defaultFont);
	GUIText.setCharacterSize(16);
	GUIText.setPosition(32, window.getSize().y / 10.0f);
	GUIText.setFillColor(sf::Color::Green);
}

void Simulation::run()
{
	initialPosition.x = window.getSize().x / 2.0f;
	initialPosition.y = window.getSize().y / 2.0f;

	initializeGUI();

	

	ball = Entity(initialPosition, initialVelocity);
	
	auto nextFrame = std::chrono::steady_clock::now();
	while (window.isOpen())
	{
		nextFrame += std::chrono::milliseconds(1000 / fps);

		handleInput();
		update();
		window.clear();
		render(window);
		window.display();

		std::this_thread::sleep_until(nextFrame);
	}
}

void Simulation::update()
{
	if (!simulate)
	{
		ball.mPosition = initialPosition;
		ball.update();
		return;
	}

	physics();
	ball.update();
}

void Simulation::onClick(int x, int y)
{
	if (currentBox)
		currentBox->deselect();

	currentBox = nullptr;

	for (auto box : textBoxes)
	{
		if (box->isClicked(x, y))
			currentBox = box;
	}

	if (currentBox)
		currentBox->select();
}

void Simulation::physics()
{
	//Adds gravity
	ball.mVelocity.y += gravity * deltaTime;

	//Collision to floor
	if (ball.mPosition.y >= floorHeight - ball.mSprite.getRadius() * 2.0f && ball.mVelocity.y > 0)
	{
		ball.mPosition.y = floorHeight - ball.mSprite.getRadius() * 2.0f;
		ball.mVelocity.y *= -elasticity;
		if (ball.mVelocity.y >= -0.4f && ball.mVelocity.y <= 0.4f)
			ball.mVelocity.y = 0;
	}

	//Collision to sides
	if (ball.mPosition.x >= window.getSize().x - ball.mSprite.getRadius() * 2.0f && ball.mVelocity.x > 0 || ball.mPosition.x <= 0 && ball.mVelocity.x < 0)
	{
		ball.mVelocity.x *= -elasticity;
		if (ball.mVelocity.x >= -0.4f && ball.mVelocity.x <= 0.4f)
			ball.mVelocity.x = 0;
	}

	//Friction
	if(isGrounded(ball))
	{
		Vector frictionVector = Vector(-ball.mVelocity);
		frictionVector.normalize();
		frictionVector *= friction;
		ball.mVelocity += frictionVector.toVector2f() * deltaTime;
	}

	/*
	float magnitude = getVectorMagnitude(ball.mVelocity);
	if (magnitude <= 1.0f)
		ball.mVelocity = ball.mVelocity - ball.mVelocity * airResistance * deltaTime;
	*/
}

void Simulation::reset()
{
	ball.mPosition = initialPosition;
	ball.mVelocity = sf::Vector2f();
}

void Simulation::handleInput()
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
		if (event.text.unicode == 13)
			{
				if(currentBox)
					currentBox->deselect();
				currentBox = nullptr;
			}

			if (currentBox)
				currentBox->handleInput(event);
			break;
		case sf::Event::MouseButtonPressed:
			onClick(event.mouseButton.x, event.mouseButton.y);
			break;
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				window.close();
				break;

			case sf::Keyboard::A:
				initialVelocity.x -= 1.f;
				initialVelocity.x = std::max(-40.0f, initialVelocity.x);
				break;

			case sf::Keyboard::D:
				initialVelocity.x += 1.f;
				initialVelocity.x = std::min(40.0f, initialVelocity.x);
				break;

			case sf::Keyboard::W:
				initialVelocity.y -= 1.f;
				initialVelocity.y = std::max(-40.0f, initialVelocity.y);
				break;

			case sf::Keyboard::S:
				initialVelocity.y += 1.f;
				initialVelocity.y = std::min(40.0f, initialVelocity.y);
				break;

			case sf::Keyboard::Left:
				initialPosition.x -= 1.f;
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
				if (simulate == true)
					reset();
				ball.mVelocity = initialVelocity * deltaTime;
				simulate = !simulate;
				break;
			}
			updateGUIText();

			break;

		default:
			break;
		}
	}
}

void Simulation::render(sf::RenderWindow &win)
{
	ball.render(win);

	for (auto box : textBoxes)
		box->render(&win);

	win.draw(GUIText);
}

bool Simulation::isGrounded(Entity& entity)
{
	return entity.mPosition.y >= floorHeight - entity.mSprite.getRadius() * 2.0f && entity.mVelocity.y == 0;
}
