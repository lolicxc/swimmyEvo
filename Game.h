#pragma once
#include  <SFML/Graphics.hpp>
#include "Screens.h"

extern Screens currentScreen;
extern sf::Font gameFont;

void InitGame();
void UpdateGame(float dt);
void DrawGame(sf::RenderWindow& window);
void RunGame();
