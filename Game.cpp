#include "Game.h"
#include "Player.h"
#include "Obstacle.h"
#include "utils.h"
#include <iostream>
#include "Background.h"
#include "MainMenu.h"
#include "Score.h"
#include "Gameover.h"
#include "Audio.h"
#include "Bullet.h"

sf::RenderWindow* gameWindow = nullptr;
Screens currentScreen = Screens::MENU;
sf::Font gameFont;



void InitGame()
{
	gameFont.openFromFile("res/collage.ttf");
	InitMainMenu();
	InitPlayer();
	InitObstacles();
	InitBackground();
	InitScore();
	InitGameover();
	PlayMusic();
}

void UpdateGame(float dt)
{

	switch (currentScreen)
	{
	case Screens::MENU:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			InitGame();
			currentScreen = Screens::GAMEPLAY;
		}
		break;

	case Screens::GAMEPLAY:
	{

		sf::Vector2f playerCenter(player.posX + player.width / 2, player.posY + player.height / 2);
		UpdateBackground(dt);
		InputPlayer();
		UpdatePlayer(dt);
		UpdateObstacles(dt);
		UpdateScore(dt);

		ShootBullets(playerCenter, *gameWindow, dt);
		UpdateBullets(dt);
		CheckCollisionBullets();

		if (player.isDead)
		{
			currentScreen = Screens::GAMEOVER;
		}
		break;
	}
	
	case Screens::GAMEOVER:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
		{
			InitGame();
			currentScreen = Screens::MENU;
		}
		break;
	}
}

void DrawGame(sf::RenderWindow& window)
{
	switch (currentScreen)
	{
	case Screens::MENU:
	{
		DrawMainMenu(window);
		sf::Text txt(gameFont);
		txt.setString("PRESS SPACE TO PLAY");
		txt.setCharacterSize(40);
		txt.setFillColor(sf::Color::White);
		txt.setPosition({ width / 2,  height - 100.0f });

		window.draw(txt);

		break;
	}

	case Screens::GAMEPLAY:
	{
		DrawBackground(window);
		DrawPlayer(window);
		DrawObstacles(window);
		DrawBullets(window);
		DrawScore(window);

		break;
	}

	case Screens::GAMEOVER:
	{
		DrawGameover(window);
		break;
	}
	}
}



void RunGame()
{
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode({ width, height }), "SwimmyEvolution");
	window.setFramerateLimit(60);
	sf::Clock clock;

	gameWindow = &window;

	InitGame();

	while (window.isOpen())
	{
		float dt = clock.restart().asSeconds();

		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
		}

		UpdateGame(dt);
		window.clear();
		DrawGame(window);
		window.display();
	}
}

