#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

using MessageContainer = std::vector<std::string>;

class Textbox{
public:
	Textbox();
	Textbox(int l_visible, int l_charSize, 
		int lWidth, sf::Vector2f l_screenPos);
	~Textbox();

	void Setup(int l_visible, int l_charSize, 
		int lWidth, sf::Vector2f l_screenPos);
	void Add(std::string l_message);
	void Clear();

	void Render(sf::RenderWindow& lWind);
private:
	MessageContainer m_messages;
	int m_numVisible;

	sf::RectangleShape mBackdrop;
	sf::Font m_font;
	sf::Text m_content;
};