#include "TextBox.h"
#include <iostream>

TextBox::TextBox(int setX, int setY, int setWidth, int setPadding, std::string setName, float* setTarget, std::string setValue, std::string setFontPath, float setFontSize) :
	x(setX),
	y(setY),
	width(setWidth),
	padding(setPadding),
	name(setName),
	value(setValue),
	fontPath(setFontPath),
	fontSize(setFontSize),
	target(setTarget)

{
	value = "INIT";

	if (!font.loadFromFile(fontPath))
		std::cout << "Failed to load font" << std::endl;

	if (setName == "")
		textName = sf::Text(name, font, fontSize);
	else
		textName = sf::Text(name + ":", font, fontSize);

	textName.setPosition(x + padding / 2, y + padding / 2);
	textName.setFillColor(sf::Color::Black);

	text = sf::Text(value, font, fontSize);
	text.setPosition(x + textName.getLocalBounds().width + padding, y + padding / 2);
	text.setFillColor(sf::Color::Black);

	height = text.getLocalBounds().height + padding * 2;

	box = sf::RectangleShape(sf::Vector2f(width, height));
	box.setFillColor(sf::Color::White);
	box.setOutlineThickness(1);
	box.setPosition(x, y);

	value = setValue;
	text.setString(value);

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
	target->draw(textName);
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
		else if (event.text.unicode != '\b')
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

	if (value == "")
		return;

	std::size_t t;
	float f = std::stof(getValue(), &t);
	std::cout << value.getSize() << " " << t << std::endl;
	if(value.getSize() == t)
	{
		*target = f;
	}
	else
	{
		value = "0";
		text.setString(value);
		*target = 0;
	}
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




