#include "TextBox.h"
#include <iostream>

TextBox::TextBox(sf::Vector2f& position, sf::Vector2f& bounds, std::string value)
{
	this->position = position;
	this->size = size;
	this->value = value;

	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
		std::cout << "Failed to load font" << std::endl;

	text = sf::Text(value, font, 20);
	text.setPosition(position);
	text.setFillColor(sf::Color::Black);

	box = sf::RectangleShape(bounds);
	box.setPosition(position);
	box.setSize(bounds);
	box.setFillColor(sf::Color::White);
}

TextBox::~TextBox()
{
	
}

void TextBox::render(sf::RenderTarget* target)
{
	target->draw(box);
	target->draw(text);
}

void TextBox::handleInput(sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::TextEntered:
		value += static_cast<char>(event.text.unicode);
		text.setString(value);
		break;

	case sf::Event::KeyPressed:

		break;
	}
}

bool TextBox::isClicked(sf::Vector2f& clickPosition) const
{
	return rect.contains(clickPosition.x, clickPosition.y);
}




