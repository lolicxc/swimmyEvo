#include "Obstacle.h"
#include "utils.h"
#include "Player.h"
#include <iostream>
#include <SFML/System/Angle.hpp> 
#include "Audio.h"


Obstacle obstacles[maxObstacles];

void InitObstacles()
{
	for (int i = 0; i < maxObstacles; i++)
	{
		obstacles[i].width = 80;
		obstacles[i].height = 80;
		obstacles[i].posY = 470;
		obstacles[i].posX = width + i * 350;
		obstacles[i].speed = 300.0f;
		obstacles[i].type = rand() % 2;
		obstacles[i].rotation = 0.0f;
		obstacles[i].rotationSpeed = -(180.0f + rand() % 180);
		obstacles[i].speedX = (i % 2 == 0) ? 100.0f : 0.0f; // solo algunos se mueven
		obstacles[i].minY = 200.0f;
		obstacles[i].maxY = 500.0f;
		obstacles[i].active = true;
		obstacles[i].respawnTimer = 0.0f;

		obstacles[i].exploding = false;
		obstacles[i].explosionTime = 0.0f;
	}
}

void UpdateObstacles(float dt)
{
	for (int i = 0; i < maxObstacles; i++)
	{
		if (obstacles[i].active)
		{
			obstacles[i].posX -= obstacles[i].speed * dt;

			//rotacion 
			obstacles[i].rotation += obstacles[i].rotationSpeed * dt;

			if (obstacles[i].rotation >= 360.0f)
				obstacles[i].rotation -= 360.0f;

			if (obstacles[i].type == 1) // volador
			{
				float fallSpeed = 150.0f;
				obstacles[i].posY += fallSpeed * dt;
				if (obstacles[i].posY > 470.0f)
					obstacles[i].posY = 470.0f; // piso
			}


			if (obstacles[i].posX < -obstacles[i].width)
			{
				float separation = 400.0f;
				float randomExtra = rand() % 500;

				int prev = (i - 1 + maxObstacles) % maxObstacles;

				obstacles[i].posX = obstacles[prev].posX + separation + randomExtra;
				obstacles[i].type = rand() % 2;
				obstacles[i].rotation = 0;
			}
			obstacles[i].posX += obstacles[i].speedX * dt;


			if (obstacles[i].posX < obstacles[i].minY || obstacles[i].posX > obstacles[i].maxY)
				obstacles[i].speedX = -obstacles[i].speedX;

		}
		else
		{
			
			if (obstacles[i].exploding)
			{
				if (obstacles[i].explosionTime == 0.0f)
				{
					PlayExplotionSound();
				}
				obstacles[i].explosionTime += dt;

				if (obstacles[i].explosionTime >= 0.5f)
				{
					obstacles[i].exploding = false;
				}
			}


			obstacles[i].respawnTimer += dt;
			if (obstacles[i].respawnTimer >= 1.5f)
			{
				obstacles[i].posX = width + rand() % 500;

				obstacles[i].type = (rand() % 10 < 7) ? 0 : 1;

				if (obstacles[i].type == 0)
				{
					obstacles[i].posY = 470.0f;
				}
				else
				{
					obstacles[i].posY = rand() % 200;
				}
				obstacles[i].rotation = 0;
				obstacles[i].active = true;
				obstacles[i].respawnTimer = 0.0f;
			}
		}
	}
	if (CheckCollisionPlayer())
	{
		player.isDead = true;
	}
}

void DrawObstacles(sf::RenderWindow& window)
{
	for (int i = 0; i < maxObstacles; i++)
	{
		if (!obstacles[i].active && !obstacles[i].exploding)
			continue;


		if (obstacles[i].exploding)
		{

			static sf::Texture explosionTexture;
			static bool expLoaded = false;

			if (!expLoaded)
			{
				explosionTexture.loadFromFile("res/obstacleAnim.png");
				expLoaded = true;
			}

			const int FRAME_COUNT = 4;
			const float TOTAL_TIME = 0.3f;
			float frameTime = TOTAL_TIME / FRAME_COUNT;

			int frame = (int)(obstacles[i].explosionTime / frameTime);
			if (frame >= FRAME_COUNT) frame = FRAME_COUNT - 1;


			int frameWidth = explosionTexture.getSize().x / FRAME_COUNT;
			int frameHeight = explosionTexture.getSize().y;

			sf::Sprite exp(explosionTexture);

			exp.setTextureRect(sf::IntRect(sf::Vector2i(frame * frameWidth, 0), sf::Vector2i(frameWidth, frameHeight)));

			exp.setOrigin({ frameWidth / 2.0f, frameHeight / 2.0f });


			exp.setPosition({ obstacles[i].posX + obstacles[i].width / 2.0f,obstacles[i].posY + obstacles[i].height / 2.0f });

			window.draw(exp);
		}
		else
		{


			static sf::Texture obstacleTexture;
			static sf::Texture obstacleTexture2;
			static bool loaded = false;
			if (!loaded)
			{
				if (!obstacleTexture.loadFromFile("res/obstacle.png"))
				{
					std::cout << "ERROR: Texture could not be loaded\n";
				}
				if (!obstacleTexture2.loadFromFile("res/obstacle2.png"))
				{
					std::cout << "ERROR: Texture could not be loaded\n";
				}
				loaded = true;
			}
			sf::Sprite sprite(obstacleTexture);
			if (obstacles[i].type == 0)
				sprite.setTexture(obstacleTexture);
			else
				sprite.setTexture(obstacleTexture2);

			sprite.setOrigin({ obstacleTexture.getSize().x / 2.0f, obstacleTexture.getSize().y / 2.0f });

			sprite.setScale({ obstacles[i].width / obstacleTexture.getSize().x, obstacles[i].height / obstacleTexture.getSize().y });

			sprite.setPosition({ obstacles[i].posX + obstacles[i].width / 2.0f, obstacles[i].posY + obstacles[i].height / 2.0f });


			sprite.setRotation(sf::degrees(obstacles[i].rotation));

			window.draw(sprite);
			// hit box
		/*    sf::RectangleShape hitbox;
			hitbox.setSize({ (float)obstacles[i].width, (float)obstacles[i].height });
			hitbox.setPosition({ obstacles[i].posX, obstacles[i].posY });
			hitbox.setFillColor(sf::Color::Transparent);
			hitbox.setOutlineColor(sf::Color::Red);
			hitbox.setOutlineThickness(2);

			window.draw(hitbox);*/
		}

	}
}

bool CheckCollisionPlayer()
{
	const float margin = 20.0f;

	for (int i = 0; i < maxObstacles; i++)
	{
		if (!obstacles[i].active) continue;

		if (player.posX < obstacles[i].posX + obstacles[i].width - margin &&
			player.posX + player.width > obstacles[i].posX + margin &&
			player.posY < obstacles[i].posY + obstacles[i].height - margin &&
			player.posY + player.height > obstacles[i].posY + margin)
		{
			return true;
		}
	}

	return false;
}
