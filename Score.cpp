#include "Score.h"
#include <iostream>
#include "Game.h"

float score = 0;
static sf::Texture scoreTexture;

void InitScore()
{
	score = 0;
	if (!scoreTexture.loadFromFile("res/score.png"))
		std::cout << "ERROR: Texture could not be loaded\n";
}

void UpdateScore(float dt)
{
	score += dt * 0.5f;
}

void DrawScore(sf::RenderWindow& window)
{

	sf::Sprite scoreSprite(scoreTexture);
	scoreSprite.setTexture(scoreTexture);
	window.draw(scoreSprite);

	sf::Text txt(gameFont);
	txt.setString(std::to_string((int)score));
	txt.setCharacterSize(40);
	txt.setFillColor(sf::Color::Black);
	txt.setPosition({ 140, 10 });
	window.draw(txt);
}
