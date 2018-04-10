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

void AudioComponent::render() {

}

void AudioComponent::update(double dt) {

}