
#include "engine.h"
#include "scenes/scn_menu.h"
#include "game.h"

MenuScene menu;

using namespace std;
using namespace sf;

int main() {
	
	Engine::Start(800, 600, "The Story of Nome", &menu);
} 
