#include "TextBox.h"
#include <iostream>
#include <SFML/Graphics.hpp>

TextBox::TextBox(int x, int y, int width, int padding, std::string value, std::string fontPath, float fontSize) :
	x(x),
	y(y),
	width(width),
	padding(padding),
	value(value),
	fontPath(fontPath),
	fontSize(fontSize)

{
	this->value = "INIT";

	if (!font.loadFromFile(fontPath))
		std::cout << "Failed to load font" << std::endl;

	text = sf::Text(value, font, fontSize);
	text.setPosition(x + padding / 2, y + padding / 2);
	text.setFillColor(sf::Color::Black);

	height = text.getLocalBounds().height + padding * 2;
	box = sf::RectangleShape(sf::Vector2f(width, height));
	box.setPosition(x, y);
	box.setFillColor(sf::Color::White);
	box.setOutlineThickness(1);

	this->value = value;
	text.setString(this->value);

}

TextBox::~TextBox()
{
	
}

TextBox::TextBox()
{
}

void TextBox::render(sf::RenderTarget* target) const
{
	target->draw(box);
	target->draw(text);
}

void TextBox::handleInput(sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::TextEntered:

		if (event.text.unicode == '\b' && value.getSize() > 0)
		{
			value.erase(value.getSize() - 1);
			text.setString(value);
		}	
		else if(event.text.unicode != '\b')
		{
			value += static_cast<char>(event.text.unicode);
			text.setString(value);
		}
		
		break;

	case sf::Event::KeyPressed:

		break;
	}
}

void TextBox::select()
{
	box.setOutlineColor(sf::Color::Red);
}

void TextBox::deselect()
{
	box.setOutlineColor(sf::Color::White);
}

std::string TextBox::getValue() const
{
	return value;
}

void TextBox::setText(std::string newText)
{
	value = newText;
	text.setString(value);
}

bool TextBox::isClicked(int x, int y) const
{
	return box.getGlobalBounds().contains(x, y);
}




