#pragma once
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>
#include <iostream>
#include <ecm.h>

using namespace sf;
using namespace std;

class AudioComponent : public Component
{
public:
	AudioComponent() = delete;
	explicit AudioComponent(Entity *p);

	void LoadAudio(const std::string &file);
	void PlayAudio();
	void QuickPlay(const std::string &file);
	void LoadMusic(const std::string &file);
	void PlayMusic();
	bool AudioIsPlaying();
	void render() override;
	void update(double dt) override;
protected:
	std::string _file;
	sf::SoundBuffer _buffer;
	sf::Sound _sound;
	sf::Music _music;
};