#pragma once
#include <SFML/Graphics.hpp>


class TextBox
{
public:
	TextBox(int x, int y, int width, int padding,std::string name, float* setTarget, std::string text = "", std::string fontPath = "arial.ttf", float fontSize = 14);
	~TextBox();
	TextBox();

	void render(sf::RenderTarget* target) const;
	bool isClicked(int x, int y) const;
	void handleInput(sf::Event& event);
	void select();
	void deselect();
	std::string getValue() const;
	void setText(std::string newText);

	std::string name;

private:
	int x;
	int y;
	int width;
	int height;
	int padding;

	float* target;

	std::string fontPath;
	float fontSize;
	sf::Font font;

	sf::String value;
	sf::Text text;
	sf::Text textName;
	sf::RectangleShape box;

	
	
};
