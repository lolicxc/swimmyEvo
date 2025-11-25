#include "Game.h"
#include "Player.h"
#include "Obstacle.h"
#include "utils.h"
#include <iostream>
#include "Background.h"


sf::RenderWindow* gameWindow = nullptr;
Screens currentScreen = Screens::MENU;
sf::Font gameFont;



void InitGame()
{
    gameFont.openFromFile("res/collage.ttf");
    InitPlayer();
    InitObstacles();
    InitBackground();
}

void UpdateGame(float dt)
{
    switch (currentScreen)
    {
    case Screens::MENU:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        {
            InitGame();             // reiniciar todo
            currentScreen = Screens::GAMEPLAY;
        }
        break;

    case Screens::GAMEPLAY:
        UpdateBackground(dt);
        InputPlayer();
        UpdatePlayer(dt);
        UpdateObstacles(dt);

        if (player.isDead)
        {
            currentScreen = Screens::GAMEOVER;
        }
        break;

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
        sf::Text txt(gameFont);
        txt.setString("PRESS SPACE TO PLAY");
        txt.setCharacterSize(40);
        txt.setFillColor(sf::Color::White);
        txt.setPosition({ 200.f, 200.f });

        window.draw(txt);

        break;
    }

    case Screens::GAMEPLAY:
    {
        DrawBackground(window);
        DrawPlayer(window);
        DrawObstacles(window);
        break;
    }

    case Screens::GAMEOVER:
    {
        sf::Text gameovertxt(gameFont);
        gameovertxt.setString("Game Over! :(");
        gameovertxt.setCharacterSize(40);
        gameovertxt.setFillColor(sf::Color::White);
        gameovertxt.setPosition({ 200.f, 200.f });

        window.draw(gameovertxt);
        break;
    }
    }
}



void RunGame()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode({ width, height }), "SFML Game");
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

