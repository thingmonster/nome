
#include "system_renderer.h"

/*

the contents of this file is largely taken from the 
platformer engine source code, but a getWindow method
has been added

*/

using namespace sf;
using namespace std;

static queue<const Drawable *> sprites;
static RenderWindow *rw;

void Renderer::initialise(sf::RenderWindow &r) {
	rw = &r;	
}

sf::RenderWindow &Renderer::getWindow() {
	return *rw;
}

void Renderer::shutdown() {
	while (!sprites.empty()) {
		sprites.pop();
	}
}

void Renderer::update(const double &) {}

void Renderer::render() {
	
	if (rw == nullptr) {
		throw("No render window set!");
	}
	
	while (!sprites.empty()) {
		rw->draw(*sprites.front());
		sprites.pop();
	}
}

void Renderer::queue(const sf::Drawable *s) {
	sprites.push(s);
}




