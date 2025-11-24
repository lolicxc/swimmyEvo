#pragma once
#include  <SFML/Graphics.hpp>

struct Player
{
	float posX;
	float posY;
	float speedY;
	bool jump;
	float height;
	float width;
	sf::RectangleShape shape;
};

extern Player player;

void InitPlayer();
void InputPlayer();
void UpdatePlayer(float dt);
void DrawPlayer(sf::RenderWindow& window);