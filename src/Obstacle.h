#pragma once
#include  <SFML/Graphics.hpp>

const int maxObstacles = 10;

struct Obstacle 
{
	float posY;
	float posX;
	float width;
	float height;
	float speed;
	int type;
	float rotation;
	float rotationSpeed;
	float speedX;
	float minY;  
	float maxY;  
	bool active;
	float respawnTimer;

	//animacion
	bool exploding;
	float explosionTime;

};

extern Obstacle obstacles[maxObstacles];

void InitObstacles();
void UpdateObstacles(float dt);
void DrawObstacles(sf::RenderWindow& window);
bool CheckCollisionPlayer();