#pragma once
#include <SFML/Graphics.hpp>


class TextBox
{
public:
	TextBox(int x, int y, int width, int padding, std::string text = "", std::string fontPath = "arial.ttf", float fontSize = 14);
	~TextBox();
	TextBox();

	void render(sf::RenderTarget* target) const;
	bool isClicked(int x, int y) const;
	void handleInput(sf::Event& event);
	void select();
	void deselect();
	std::string getValue() const;
	void setText(std::string newText);

private:
	int x;
	int y;
	int width;
	int height;
	int padding;

	std::string fontPath;
	float fontSize;
	sf::Font font;

	sf::String value;
	sf::Text text;
	sf::RectangleShape box;
	
};
