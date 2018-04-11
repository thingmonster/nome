#include "cmp_audio.h"
#include <iostream>

AudioComponent::AudioComponent(Entity* p) :Component(p) {}

void AudioComponent::LoadAudio(const std::string &file)
{
	_file = file;

	if (!_buffer.loadFromFile("res/fx/" + _file))
	{
		std::cout << "ERROR" << std::endl;
	}
}

void AudioComponent::PlayAudio()
{
	_sound.setBuffer(_buffer);
	_sound.play();
}

bool AudioComponent::AudioIsPlaying()
{
	if (_sound.getStatus() == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void AudioComponent::render() {

}

void AudioComponent::update(double dt) {

}