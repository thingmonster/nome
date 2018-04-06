
#include "engine.h"
#include "scenes/scn_menu.h"
#include "scenes/scn_options.h"
#include "scenes/scn_remap.h"
#include "scenes/scn_paused.h"
#include "scenes/scn_level1.h"
#include "game.h"

MenuScene menu;
OptionsScene options;
RemapScene remap;
PausedScene paused;
Level1Scene level1;

using namespace std;
using namespace sf;

int main() {
	
	Engine::Start(800, 600, "The Story of Nome", &menu);
} 
