#include "Gameover.h"
#include <iostream>

static sf::Texture gameoverText;

void InitGameover()
{
	if (!gameoverText.loadFromFile("res/gameOver.png"))
		std::cout << "ERROR: no se pudo cargar la textura\n";

}
void DrawGameover(sf::RenderWindow& window)
{
	sf::Sprite gameOverSprite(gameoverText);
	gameOverSprite.setTexture(gameoverText);
	window.draw(gameOverSprite);

}