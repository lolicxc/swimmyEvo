#include "Player.h"

Player player;

void InitPlayer()
{
	player.posX = 240;
	player.posY = 450;
	player.speedY = -200.0f;
	player.jump = false;
	player.width = 90.0f;
	player.height = 70.0f;
	player.shape.setSize({ player.width, player.height });
	player.shape.setFillColor(sf::Color::Red);
}

void InputPlayer()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		player.jump = true;
	}
}

void UpdatePlayer(float dt)
{
	float gravity = 1000.0f;
	float jumpForce = -450.0f;
	float playerFloor = 450.0f;

	//player.speed += gravity * GetFrameTime();

	//// salto
	//if (player.moveUp)
	//{
	//	player.speed = jumpForce;
	//	player.moveUp = false;
	//}

	//player.playerFigure.y += player.speed * GetFrameTime();
	player.speedY += gravity * dt;
	if (player.jump)
	{
		player.speedY = jumpForce;
		player.jump = false;
	}
	player.posY += player.speedY * dt;
	if (player.posY >= playerFloor)
	{
		player.posY = playerFloor;
	}
}

void DrawPlayer(sf::RenderWindow& window)
{
	player.shape.setPosition({ player.posX, player.posY });
	window.draw(player.shape);
}
