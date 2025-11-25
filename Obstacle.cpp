#include "Obstacle.h"
#include "utils.h"
#include "Player.h"
#include <iostream>
Obstacle obstacles[maxObstacles];

void InitObstacles()
{
    for (int i = 0; i < maxObstacles; i++)
    {
        obstacles[i].width = 40;
        obstacles[i].height = 50;
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
            obstacles[i].posX = width + 800 + rand() % 600;
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
        sf::RectangleShape rect;
        rect.setSize({ (float)obstacles[i].width, (float)obstacles[i].height });
        rect.setPosition({ obstacles[i].posX, obstacles[i].posY });
        rect.setFillColor(sf::Color::Green);

        window.draw(rect);
    }
}

bool CheckCollisionPlayer()
{
    for (int i = 0; i < maxObstacles; i++)
    {
        if (player.posX < obstacles[i].posX + obstacles[i].width &&
            player.posX + player.width > obstacles[i].posX &&
            player.posY < obstacles[i].posY + obstacles[i].height &&
            player.posY + player.height > obstacles[i].posY)
        {
            return true;
        }
    }

    return false;
}
