#include "Audio.h"
#include <iostream>

static sf::SoundBuffer buffer("res/jump.wav");
static sf::SoundBuffer buffer2("res/shoot.wav");
static sf::SoundBuffer buffer3("res/explotion.wav");
static sf::Sound jumpSound(buffer);
static sf::Sound shootSound(buffer2);
static sf::Sound explotionSound(buffer3);


sf::Music music;


void PlayJumpSound()
{
	jumpSound.play();
}

void PlayShootSound()
{
    shootSound.play();
}

void PlayExplotionSound()
{
    explotionSound.play();
}

void PlayMusic()
{

    if (!music.openFromFile("res/gameplay.wav"))
    {
        std::cout << "Error cargando música\n";
        return;
    }

    music.setLoopPoints({ sf::milliseconds(500), sf::seconds(7) });
    music.setLooping(true);
    music.play();
}
