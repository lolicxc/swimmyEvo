#pragma once
#include <SFML/Graphics.hpp>


struct BackGround
{
	sf::Texture part2;
	sf::Texture part3;
	sf::Texture part4;
	sf::Texture part5;

	float scrollPart2 = 0.0f;
	float scrollPart3 = 0.0f;
	float scrollPart4 = 0.0f;
	float scrollPart5 = 0.0f;
};

extern BackGround gameBackGround;

void InitBackground();
void UpdateBackground(float dt);
void DrawBackground(sf::RenderWindow& window);
