// Background.h
#pragma once
#include <SFML/Graphics.hpp>

struct Background
{
    sf::Texture texture; // solo la textura
};

extern Background background;

void InitBackground();
void DrawBackground(sf::RenderWindow& window);
