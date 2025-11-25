#include "Obstacle.h"
#include "utils.h"
#include "Player.h"
#include <iostream>
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
    }
}

void UpdateObstacles(float dt)
{
    for (int i = 0; i < maxObstacles; i++)
    {
        obstacles[i].posX -= obstacles[i].speed * dt;

        if (obstacles[i].posX < -obstacles[i].width)
        {
            float separation = 700.0f;            // separación mínima entre obstáculos
            float randomExtra = rand() % 500;     // distancia aleatoria adicional

            int prev = (i - 1 + maxObstacles) % maxObstacles;

            obstacles[i].posX = obstacles[prev].posX + separation + randomExtra;
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
       static sf::Texture obstacleTexture;
       static bool loaded = false;
        if (!loaded)
        {
            if (!obstacleTexture.loadFromFile("res/obstacle.png"))
            {
                std::cout << "ERROR: no se pudo cargar la textura\n";
            }
            loaded = true;
        }
        sf::Sprite sprite(obstacleTexture);
        sprite.setPosition({ obstacles[i].posX, obstacles[i].posY});
        sprite.setScale({ obstacles[i].width / obstacleTexture.getSize().x ,
            obstacles[i].height / obstacleTexture.getSize().y});

        window.draw(sprite);
        // --- DEBUG HITBOX ---
        sf::RectangleShape hitbox;
        hitbox.setSize({ (float)obstacles[i].width, (float)obstacles[i].height });
        hitbox.setPosition({ obstacles[i].posX, obstacles[i].posY });
        hitbox.setFillColor(sf::Color::Transparent);
        hitbox.setOutlineColor(sf::Color::Red);
        hitbox.setOutlineThickness(2);

        window.draw(hitbox);
    }
}

bool CheckCollisionPlayer()
{
    const float margin = 20.0f;

    for (int i = 0; i < maxObstacles; i++)
    {
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
