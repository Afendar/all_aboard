#pragma once

#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

class Sound {
	public:
		Sound(std::string name);
		virtual ~Sound();
		static void initSound();
		void play();

		static Sound* m_hit;
		static Sound* m_pickup;
		static Sound* m_unlock;

	private:
		sf::SoundBuffer m_buffer;
		sf::Sound m_sound;
};