#pragma once
#include  <SFML/Graphics.hpp>

const int maxObstacles = 3;

struct Obstacle 
{
	float posY;
	float posX;
	float width;
	float height;
	float speed;
};

extern Obstacle obstacles[maxObstacles];

void InitObstacles();
void UpdateObstacles(float dt);
void DrawObstacles(sf::RenderWindow& window);
bool CheckCollisionPlayer();