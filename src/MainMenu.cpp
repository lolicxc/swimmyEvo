#include "MainMenu.h"
#include <iostream>

static sf::Texture menuBGTexture;

void InitMainMenu()
{
	if (!menuBGTexture.loadFromFile("res/backgroundMenu.png"))
		std::cout << "ERROR: Texture could not be loaded\n";
}

void DrawMainMenu(sf::RenderWindow& window)
{
	sf::Sprite menuBackground(menuBGTexture);
	menuBackground.setTexture(menuBGTexture);
	window.draw(menuBackground);
}
