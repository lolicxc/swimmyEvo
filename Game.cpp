#include "Game.h"
#include "Player.h"


sf::RenderWindow* gameWindow = nullptr;

void InitGame()
{
    InitPlayer();
}

void UpdateGame(float dt)
{
    InputPlayer();
    UpdatePlayer(dt);
}

void DrawGame(sf::RenderWindow& window)
{
    DrawPlayer(window);
}

void RunGame()
{
    const int width = 1080;
    const int height = 720;

    sf::RenderWindow window(sf::VideoMode({ width, height }), "SFML Game");
    window.setFramerateLimit(60);
    sf::Clock clock;

    gameWindow = &window;

    InitGame(); // ?? Inicializamos TODO el juego (player, enemigos, mapas, etc)

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        UpdateGame(dt);      // ?? Lógica
        window.clear();
        DrawGame(window);    // ?? Dibujos
        window.display();
    }
}
