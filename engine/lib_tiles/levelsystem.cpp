#define _USE_MATH_DEFINES
#include<cmath>

#include <iostream>
#include "levelsystem.h"
#include "maths.h"
#include <fstream>

using namespace std;
using namespace sf;



std::unique_ptr<LevelSystem::TILE[]> LevelSystem::_tiles;
size_t LevelSystem::_width;
size_t LevelSystem::_height;

float LevelSystem::_tileSize(100.f);
vector<std::unique_ptr<sf::RectangleShape>> LevelSystem::_sprites;

std::map<LevelSystem::TILE, sf::Color> LevelSystem::_colours {
	{WALL, Color::White}, 
	{START, Color::Red}, 
	{END, Color::Green}, 
	{EMPTY, Color::Black}, 
	{WAYPOINT, Color::Blue},
	{ENEMY, Color::Black}
};



size_t LevelSystem::getHeight() {
	return _height;
}

size_t LevelSystem::getWidth() {
	return _width;
}

float LevelSystem::getTileSize() {
	return _tileSize;
}

sf::Vector2ul LevelSystem::screenCoordsToIndexes(sf::Vector2f pos) {
	pos /= _tileSize;
	return (Vector2ul)pos;
}



LevelSystem::TILE LevelSystem::getTileAt(sf::Vector2f v) {
	
	size_t index = (v.y * _width) + v.x;
	return _tiles[index];
}

LevelSystem::TILE LevelSystem::getTileFromScreenCoords(sf::Vector2f v) {
	
	size_t x = floor(v.x) / _tileSize;
	size_t y = floor(v.y) / _tileSize;
	
	size_t index = (y * _width) + x;
	return _tiles[index];
}

LevelSystem::TILE LevelSystem::getTile(sf::Vector2ul v) {
	
	size_t index = (v.y * _width) + v.x;
	return _tiles[index];
}

sf::Vector2f LevelSystem::getTilePosition(sf::Vector2ul v) {
	
	float xPos = v.x * _tileSize;
	float yPos = v.y * _tileSize;
	return {xPos, yPos};	
}

sf::Vector2f LevelSystem::getTileCentre(sf::Vector2ul v) {
	
	float xPos = v.x * _tileSize + _tileSize / 2;
	float yPos = v.y * _tileSize + _tileSize / 2;
	return {xPos, yPos};	
}

sf::Vector2f LevelSystem::getTileCoordinates(TILE t) {
	
	size_t index;
	
	for (size_t i = 0; i < _width * _height; i++) {
		if (_tiles[i] == t) {
			index = i;
		}
	}
	
	size_t x = (index % _width);
	size_t y = floor(index / _width);
	
	sf::Vector2f coords = getTilePosition({x,y});
	
	coords.x += _tileSize / 2;
	coords.y += _tileSize / 2;
	
	return coords;
}

vector<sf::Vector2ul> LevelSystem::findTiles(TILE t) {
	
	vector<sf::Vector2ul> coords;
	
	size_t x;
	size_t y;
	sf::Vector2ul v = {0,0};
	
	
	for (size_t i = 0; i < _width * _height; i++) {
		if (_tiles[i] == t) {
			
			size_t x = (i % _width);
			size_t y = floor(i / _width);
			v = {x,y};
			coords.push_back(v);
	
		}
	}
	
	return coords;
}

sf::Color LevelSystem::getColor(LevelSystem::TILE t) {
	auto it = _colours.find(t);
	if (it == _colours.end()) {
		_colours[t] = Color::Transparent;
	}
	return _colours[t];
}
 
void LevelSystem::setColor(LevelSystem::TILE t, sf::Color c) {
	_colours[t] = c;
}




void LevelSystem::loadLevel(const std::string &path, float tileSize) {
	
	_tileSize = tileSize;
	size_t w = 0, h = 0;
	string buffer;

	ifstream f(path);
	if (f.good()) {
		f.seekg(0, std::ios::end);
		buffer.resize(f.tellg());
		f.seekg(0);
		f.read(&buffer[0], buffer.size());
		f.close();
	} else {
		throw string("Couldn't open level file: ") + path;
	}
	
	std::vector<TILE> temp_tiles;
	for (int i = 0; i < buffer.size(); ++i) {
		const char c = buffer[i];
		switch (c) {
			case 'w':
				temp_tiles.push_back(WALL);
				break;
			case 's':
				temp_tiles.push_back(START);
				break;
			case 'e':
				temp_tiles.push_back(END);
				break;
			case ' ':
				temp_tiles.push_back(EMPTY);
				break;
			case '+':
				temp_tiles.push_back(WAYPOINT);
				break;
			case 'n':
				temp_tiles.push_back(ENEMY);
				break;
			case '\n':
				if (w == 0) {
					w = i;
				}
				h++;
				break;
			default:
				// cout << c << endl;
				;
		}
	}
	if (temp_tiles.size() != (w * h)) {
		throw string("Can't parse level file: ") + path;
	}
	
	_tiles = std::make_unique<TILE[]>(w * h);
	_width = w;	
	_height = h;
	std::copy(temp_tiles.begin(), temp_tiles.end(), &_tiles[0]);
	cout << "Level " << path << " Loaded. " << w << "x" << h << std::endl;
	buildSprites();

}

void LevelSystem::buildSprites() {
	
	_sprites.clear();
	
	for (size_t y = 0; y < LevelSystem::getHeight(); ++y) {
		for (size_t x = 0; x < LevelSystem::getWidth(); ++x) {
			auto s = make_unique<sf::RectangleShape>();
			s->setPosition(getTilePosition({x, y}));
			s->setSize(Vector2f(_tileSize, _tileSize));
			s->setFillColor(getColor(getTile({x, y})));
			_sprites.push_back(move(s)); 
		}
	}
}


		
void LevelSystem::render(RenderWindow &window) {
	for (size_t i = 0; i < _width * _height; ++i) {
		window.draw(*_sprites[i]);
	}
}


