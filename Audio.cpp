#include "Audio.h"
#include <iostream>

static sf::SoundBuffer buffer("res/jump.wav");
static sf::Sound jumpSound(buffer);
static sf::Music music("res/gameplay.wav");


void PlayJumpSound()
{
	jumpSound.play();
}

void PlayMusic()
{
	music.play();
	music.setLoopPoints({ sf::milliseconds(500), sf::seconds(30) });
}
