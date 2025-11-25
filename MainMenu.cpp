#include "MainMenu.h"
#include <iostream>

static sf::Texture menuBGTexture;

void InitMainMenu()
{
	if (!menuBGTexture.loadFromFile("res/backgroundMenu.png"))
		std::cout << "ERROR: no se pudo cargar la textura\n";
}

void DrawMainMenu(sf::RenderWindow& window)
{
	sf::Sprite menuBackground(menuBGTexture);
	menuBackground.setTexture(menuBGTexture);
	window.draw(menuBackground);
}
