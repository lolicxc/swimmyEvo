#include "Bullet.h"
#include "Obstacle.h"

Bullets bullets[maxBullets];
float bulletSpeed = 600.0f;
float shootCooldown = 0.2f;
float lastShotTime = 0.0f;



void ShootBullets(sf::Vector2f playerPos, sf::RenderWindow& window, float dt)
{
	lastShotTime += dt;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && lastShotTime >= shootCooldown)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);

		sf::Vector2f direction(mousePos.x - playerPos.x, mousePos.y - playerPos.y);
		float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		if (length == 0) return;
		direction.x /= length;
		direction.y /= length;

		for (int i = 0; i < maxBullets; i++)
		{
			if (!bullets[i].active)
			{
				bullets[i].shape = sf::CircleShape(10.0f);
				bullets[i].shape.setFillColor(sf::Color::Cyan);
				bullets[i].shape.setPosition(playerPos);
				bullets[i].velocity = direction * bulletSpeed;
				bullets[i].active = true;
				break;
			}
		}

		lastShotTime = 0.0f;
	}
}

void UpdateBullets(float dt)
{
	for (int i = 0; i < maxBullets; i++)
	{
		if (bullets[i].active)
		{
			bullets[i].shape.move(bullets[i].velocity * dt);
			sf::Vector2f pos = bullets[i].shape.getPosition();
			if (pos.x < 0 || pos.x > 1920 || pos.y < 0 || pos.y > 1080)
				bullets[i].active = false;
		}
	}
}

void DrawBullets(sf::RenderWindow& window)
{
	for (int i = 0; i < maxBullets; i++)
	{
		if (bullets[i].active)
			window.draw(bullets[i].shape);
	}
}

bool CheckCollisionBullets()
{
	for (int i = 0; i < maxBullets; i++)
	{
		if (!bullets[i].active) continue;

		for (int j = 0; j < maxObstacles; j++)
		{
			if (!obstacles[j].active) continue;

			float bulletX = bullets[i].shape.getPosition().x;
			float bulletY = bullets[i].shape.getPosition().y;
			float bulletSize = bullets[i].shape.getRadius() * 2;

			if (bulletX < obstacles[j].posX + obstacles[j].width &&
				bulletX + bulletSize > obstacles[j].posX &&
				bulletY < obstacles[j].posY + obstacles[j].height &&
				bulletY + bulletSize > obstacles[j].posY)
			{
				bullets[i].active = false;
				obstacles[j].active = false; 
				return true;
			}
		}
	}

	return false;
}
