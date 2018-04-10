#include "game.h"
#include <Windows.h>
//#include <SFML/Audio.hpp>
//#include <iostream>	

MenuScene menu;
OptionsScene options;
RemapScene remap;
PausedScene paused;
SaveScene save;
LoadScene loadGame;
Level1Scene level1;

using namespace std;
using namespace sf;

int main() {
	//testing sound fx
	
	/*sf::SoundBuffer buffer;
	sf::Sound sound;

	if (!buffer.loadFromFile("res/fx/Level_Complete.wav"))
	{
		std::cout << "ERROR" << std::endl;
	}

	sound.setBuffer(buffer);
	sound.play();
	*/
	// FreeConsole();//Hides CMD window	
	Engine::Start(800, 600, "The Story of Nome", &menu);
	
} 







