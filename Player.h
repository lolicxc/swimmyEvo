#pragma once
#include  <SFML/Graphics.hpp>

struct Player
{
	float posX;
	float posY;
	float speedY;
	bool jump;
	int jumpCount;
	int maxJumps;
	float height;
	float width;
	sf::RectangleShape shape;
	bool wasPressed;
};

extern Player player;

void InitPlayer();
void InputPlayer();
void UpdatePlayer(float dt);
void DrawPlayer(sf::RenderWindow& window);