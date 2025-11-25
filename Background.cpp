#include <SFML/Graphics.hpp>
#include <iostream>
#include "Background.h"


BackGround gameBackGround;

void InitBackground()
{
	if (!gameBackGround.part2.loadFromFile("res/Background/Plan 2.png"))
		std::cout << "Error cargando Plan 2\n";
	if (!gameBackGround.part3.loadFromFile("res/Background/Plan 3.png"))
		std::cout << "Error cargando Plan 3\n";
	if (!gameBackGround.part4.loadFromFile("res/Background/Plan 4.png"))
		std::cout << "Error cargando Plan 4\n";
	if (!gameBackGround.part5.loadFromFile("res/Background/Plan 5.png"))
		std::cout << "Error cargando Plan 5\n";

	gameBackGround.scrollPart2 = 0;
	gameBackGround.scrollPart3 = 0;
	gameBackGround.scrollPart4 = 0;
	gameBackGround.scrollPart5 = 0;
}

void UpdateBackground(float dt)
{
	gameBackGround.scrollPart2 -= 160.0f * dt;
	gameBackGround.scrollPart3 -= 130.0f * dt;
	gameBackGround.scrollPart4 -= 110.0f * dt;
	gameBackGround.scrollPart5 -= 90.0f * dt;

	if (gameBackGround.scrollPart2 <= -(int)gameBackGround.part2.getSize().x) gameBackGround.scrollPart2 = 0;
	if (gameBackGround.scrollPart3 <= -(int)gameBackGround.part3.getSize().x) gameBackGround.scrollPart3 = 0;
	if (gameBackGround.scrollPart4 <= -(int)gameBackGround.part4.getSize().x) gameBackGround.scrollPart4 = 0;
	if (gameBackGround.scrollPart5 <= -(int)gameBackGround.part5.getSize().x) gameBackGround.scrollPart5 = 0;
}

void DrawBackground(sf::RenderWindow& window)
{


	// --- Capa 5 ---
	sf::Sprite sprite5(gameBackGround.part5);
	sprite5.setTexture(gameBackGround.part5);
	sprite5.setPosition({ gameBackGround.scrollPart5, 0 });
	window.draw(sprite5);
	sprite5.setPosition({ gameBackGround.scrollPart5 + gameBackGround.part5.getSize().x, 0 });
	window.draw(sprite5);

	// --- Capa 4 ---
	sf::Sprite sprite4(gameBackGround.part4);
	sprite4.setTexture(gameBackGround.part4);
	sprite4.setPosition({ gameBackGround.scrollPart4, 50 });
	window.draw(sprite4);
	sprite4.setPosition({ gameBackGround.scrollPart4 + gameBackGround.part4.getSize().x, 50 });
	window.draw(sprite4);

	// --- Capa 3 ---
	sf::Sprite sprite3(gameBackGround.part3);
	sprite3.setTexture(gameBackGround.part3);
	sprite3.setPosition({ gameBackGround.scrollPart3, 330 });
	window.draw(sprite3);
	sprite3.setPosition({ gameBackGround.scrollPart3 + gameBackGround.part3.getSize().x, 330 });
	window.draw(sprite3);

	// --- Piso (capa 2) ---
	sf::Sprite sprite2(gameBackGround.part2);
	sprite2.setTexture(gameBackGround.part2);
	float floorY = window.getSize().y - gameBackGround.part2.getSize().y;
	sprite2.setPosition({ gameBackGround.scrollPart2, floorY });
	window.draw(sprite2);
	sprite2.setPosition({ gameBackGround.scrollPart2 + gameBackGround.part2.getSize().x, floorY });
	window.draw(sprite2);
}


