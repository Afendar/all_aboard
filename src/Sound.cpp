#include "Sound.h"

Sound* Sound::m_hit;
Sound* Sound::m_pickup;
Sound* Sound::m_unlock;

Sound::Sound(std::string name)
{
	m_buffer.loadFromFile(name);
}

Sound::~Sound()
{
}

void Sound::initSound()
{
	m_hit = new Sound("sfx/hit.wav");
	m_pickup = new Sound("sfx/pickup.wav");
	m_unlock = new Sound("sfx/unlock.wav");
}

void Sound::play()
{
	m_sound.setBuffer(m_buffer);
	m_sound.play();
}
