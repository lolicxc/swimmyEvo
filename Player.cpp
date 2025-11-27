#include "Player.h"
#include <iostream>
#include "Audio.h"
Player player;
static sf::Texture playerTexture;

void InitPlayer()
{
	player.posX = 240;
	player.posY = 450;
	player.speedY = -200.0f;
	player.jump = false;
	player.width = 140.0f;
	player.height = 90.0f;
	player.wasPressed = false;
	player.jumpCount = 0;
	player.maxJumps = 2;
	player.isDead = false;
	player.frame = 0;
	player.animTimer = 0.0;
	player.frameTime = 0.1f;
	if (!playerTexture.loadFromFile("res/playerAnima.png"))
		std::cout << "ERROR: Texture could not be loaded\n";

	player.angleDeg = 0;      
	player.mouthOffset = { 0, 0 };

}

void InputPlayer()
{
	bool pressing = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);

	if (pressing && !player.wasPressed)
	{
		if (player.jumpCount < player.maxJumps)
			player.jump = true;
	}

	player.wasPressed = pressing;
}

void UpdatePlayer(float dt, sf::RenderWindow& window)
{
	float gravity = 1000.0f;
	float jumpForce = -550.0f;
	float playerFloor = 470.0f;

	player.speedY += gravity * dt;
	if (player.jump)
	{

		PlayJumpSound();
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

	player.animTimer += dt;
	if (player.animTimer >= player.frameTime)
	{
		player.frame++;
		int totalFrames = playerTexture.getSize().x / 177;
		if (player.frame >= totalFrames)
			player.frame = 0;

		player.animTimer = 0.0f;
	}

	sf::Vector2i mouse = sf::Mouse::getPosition(window);
	sf::Vector2f playerCenter({ player.posX + player.width * 0.5f,player.posY + player.height * 0.5f });

	float dx = mouse.x - playerCenter.x;
	float dy = mouse.y - playerCenter.y;

	float angle = atan2(dy, dx) * 180.f / 3.14159f;


	if (angle < -60.f) angle = -60.f;
	if (angle > 60.f) angle = 60.f;

	player.angleDeg = angle;

	float mouthDistance = 60.f; 
	player.mouthOffset = {
		cos(angle * 3.14159f / 180.f) * mouthDistance,
		sin(angle * 3.14159f / 180.f) * mouthDistance
	};

}

void DrawPlayer(sf::RenderWindow& window)
{
	const float frameW = 177.0f;
	const float frameH = 128.0f;

	sf::Sprite sprite(playerTexture);
	sprite.setTextureRect({ { player.frame * 177, 0}, {177, 177 } });
	sprite.setOrigin({ frameW / 2.f, frameH / 2.f });
	sprite.setScale({ player.width / frameW, player.height / frameH });
	sprite.setPosition({ player.posX + player.width / 2.f,
		player.posY + player.height / 2.f });
	sprite.setRotation(sf::degrees(player.angleDeg));
	window.draw(sprite);

	// hitbox
	//sf::RectangleShape hitbox;
	//hitbox.setSize({ player.width, player.height});
	//hitbox.setPosition({ player.posX, player.posY });
	//hitbox.setFillColor(sf::Color::Transparent); 
	//hitbox.setOutlineColor(sf::Color::Blue);     
	//hitbox.setOutlineThickness(2.0f);

	//window.draw(hitbox);
}

