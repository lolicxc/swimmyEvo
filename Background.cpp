// Background.cpp
#include "Background.h"
#include <iostream>
#include "utils.h"

Background background;

void InitBackground()
{
    if (!background.texture.loadFromFile("res/background.png"))
    {
        std::cout << "ERROR: no se pudo cargar la textura\n";
    }
}

void DrawBackground(sf::RenderWindow& window)
{
    sf::Sprite sprite(background.texture); // sprite local
    sprite.setScale({
        float(width) / float(background.texture.getSize().x),
        float(height) / float(background.texture.getSize().y) }
    );
    window.draw(sprite);
}
