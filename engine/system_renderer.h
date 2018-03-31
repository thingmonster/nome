#pragma once
#include <SFML/Graphics.hpp>
#include <queue>
#include <iostream>

namespace Renderer {
	
	void initialise(sf::RenderWindow &);
	sf::RenderWindow &getWindow();
	
	void shutdown();
	void update(const double &);
	void queue(const sf::Drawable *s);
	void render();
}