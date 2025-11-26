#pragma once
#include  <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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
	bool wasPressed;
	bool isDead;

	int frame;
	float animTimer;
	float frameTime;

};

extern Player player;

void InitPlayer();
void InputPlayer();
void UpdatePlayer(float dt);
void DrawPlayer(sf::RenderWindow& window);