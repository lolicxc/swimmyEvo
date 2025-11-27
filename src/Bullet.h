#pragma once
#include <SFML/Graphics.hpp>


const int maxBullets = 50;

struct Bullets
{
	sf::CircleShape shape;
	sf::Vector2f velocity;
	bool active = false;
};

extern Bullets bullets[maxBullets];
extern float bulletSpeed;
extern float shootCooldown;
extern float lastShotTime;

void ShootBullets(sf::Vector2f playerPos, sf::RenderWindow& window, float dt);
void UpdateBullets(float dt);
void DrawBullets(sf::RenderWindow& window);
bool CheckCollisionBullets();