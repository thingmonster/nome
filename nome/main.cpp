#include "game.h"
#include <Windows.h>

MenuScene menu;
OptionsScene options;
RemapScene remap;
PausedScene paused;
SaveScene save;
LoadScene loadGame;
Level1Scene level1;
DeathScene death;

using namespace std;
using namespace sf;

int main() {
	FreeConsole();//Hides CMD window	
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	Engine::Start(800, 600, "The Story of Nome", &menu);	
} 







