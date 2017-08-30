#pragma once
#include <SFML/Graphics.hpp>

namespace sf 
{
	class Event;
}

class TextBox
{
public:
	TextBox(sf::Vector2f& position, sf::Vector2f& size, std::string value = "0");
	~TextBox();

	void render(sf::RenderTarget* target);
	bool isClicked(sf::Vector2f& clickPosition) const;
	void handleInput(sf::Event& event);

private:
	sf::Vector2f position;
	sf::Vector2f size;
	sf::String value;
	sf::Text text;
	sf::FloatRect rect;
	sf::RectangleShape box;
};
