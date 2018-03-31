
#include "engine.h"

using namespace std;
using namespace sf;

void Engine::Start(int width, int height, const std::string& name) {
	
	RenderWindow window(sf::VideoMode(width, height), name);
	window.setVerticalSyncEnabled(true);
	
	while (window.isOpen()) {
		
		Event event;
    while (window.pollEvent(event)) {
      if (event.type == Event::Closed) {
        window.close();
      }
    }
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
      window.close();
		}
		
		cout << "started" << endl;
	}
}