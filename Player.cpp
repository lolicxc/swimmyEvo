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
	player.wasPressed = false;
	player.jumpCount = 0;
	player.maxJumps = 2;
}

void InputPlayer()
{
	bool pressing = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);

	if (pressing && !player.wasPressed)
	{
		if (player.jumpCount < player.maxJumps)
			player.jump = true;
	}

	player.wasPressed = pressing;
}

void UpdatePlayer(float dt)
{
	float gravity = 1000.0f;
	float jumpForce = -450.0f;
	float playerFloor = 450.0f;

	player.speedY += gravity * dt;
	if (player.jump)
	{
		player.speedY = jumpForce;
		player.jump = false;
		player.jumpCount++;
	}
	player.posY += player.speedY * dt;
	
	if (player.posY >= playerFloor)
	{
		player.posY = playerFloor;
		player.speedY = 0;

		player.jumpCount = 0;   
	}

}

void DrawPlayer(sf::RenderWindow& window)
{
	player.shape.setPosition({ player.posX, player.posY });
	window.draw(player.shape);
}
