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
        obstacles[i].type = rand() % 2;
    }
}

void UpdateObstacles(float dt)
{
    for (int i = 0; i < maxObstacles; i++)
    {
        obstacles[i].posX -= obstacles[i].speed * dt;

        if (obstacles[i].posX < -obstacles[i].width)
        {
            float separation = 700.0f;            
            float randomExtra = rand() % 500;     

            int prev = (i - 1 + maxObstacles) % maxObstacles;

            obstacles[i].posX = obstacles[prev].posX + separation + randomExtra;
            obstacles[i].type = rand() % 2;
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
       static sf::Texture obstacleTexture2;
       static bool loaded = false;
        if (!loaded)
        {
            if (!obstacleTexture.loadFromFile("res/obstacle.png"))
            {
                std::cout << "ERROR: no se pudo cargar la textura\n";
            }
            if (!obstacleTexture2.loadFromFile("res/obstacle2.png"))
            {
                std::cout << "ERROR cargando obstacle2.png\n";
            }
            loaded = true;
        }
        sf::Sprite sprite(obstacleTexture);
        if (obstacles[i].type == 0)
            sprite.setTexture(obstacleTexture);
        else
            sprite.setTexture(obstacleTexture2);

        sprite.setPosition({ obstacles[i].posX, obstacles[i].posY});
        sprite.setScale({ obstacles[i].width / obstacleTexture.getSize().x ,
            obstacles[i].height / obstacleTexture.getSize().y});

        window.draw(sprite);
        // hit box
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
  