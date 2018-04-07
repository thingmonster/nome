
#include "game.h"

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
	
	Engine::Start(800, 600, "The Story of Nome", &menu);
} 
