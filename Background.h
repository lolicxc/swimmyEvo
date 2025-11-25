#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

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

// Inicializa las texturas y los valores de scroll
void InitBackground();

// Actualiza el scroll de cada capa, recibe dt
void UpdateBackground(float dt);

// Dibuja todas las capas en la ventana
void DrawBackground(sf::RenderWindow& window);
