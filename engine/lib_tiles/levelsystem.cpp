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
sf::Vector2f LevelSystem::_offset;

sf::Texture LevelSystem::texture;
float LevelSystem::_tileSize(100.f);
vector<std::unique_ptr<sf::RectangleShape>> LevelSystem::_sprites;




std::map<LevelSystem::TILE, sf::Color> LevelSystem::_colours {
	{WALL, Color::White}, 
	{START, Color::White}, 
	{BALL, Color::White}, 
	{EMPTY, Color::White}, 
	{HOLE, Color::White}
};

std::map<LevelSystem::TILE, sf::IntRect> LevelSystem::_spriteCoords {
	{WALL, sf::IntRect(150, 0, 150, 150)}, 
	{START, sf::IntRect(0, 0, 150, 150)}, 
	{BALL, sf::IntRect(0, 0, 150, 150)}, 
	{EMPTY, sf::IntRect(0, 0, 150, 150)}, 
	{HOLE, sf::IntRect(300, 0, 150, 150)}
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

sf::Vector2f LevelSystem::getOffset() {
	return _offset;
}

void LevelSystem::resize(const std::string& sprites, sf::Vector2f windowSize) {
	
	
	cout << windowSize.x << endl;
	cout << windowSize.y << endl;
	
	if (windowSize.x / _width > windowSize.y / _height) {
		_tileSize = windowSize.y / _height;
		_offset = Vector2f((windowSize.x - _tileSize * _width) / 2, 0);
	} else {
		_tileSize = windowSize.x / _width;
		_offset = Vector2f(0, (windowSize.y - _tileSize * _height) / 2);
	}
	
	for (size_t y = 0; y < LevelSystem::getHeight(); ++y) {
		for (size_t x = 0; x < LevelSystem::getWidth(); ++x) {
			
			Vector2f pos = getTilePosition({x, y});
			_sprites[x + _width * y]->setPosition(getTilePosition({x, y}));
			_sprites[x + _width * y]->setSize(Vector2f(_tileSize, _tileSize));
			
		}
	}
	
}

sf::Vector2ul LevelSystem::screenCoordsToIndexes(sf::Vector2f pos) {
	pos.x = (pos.x - _offset.x) / _tileSize;
	pos.y = (pos.y - _offset.y) / _tileSize;
	return (Vector2ul)pos;
}



LevelSystem::TILE LevelSystem::getTileAt(sf::Vector2f v) {
	
	size_t index = (v.y * _width) + v.x;
	return _tiles[index];
}

LevelSystem::TILE LevelSystem::getTileFromScreenCoords(sf::Vector2f v) {
	
	size_t x = floor(v.x - _offset.x) / _tileSize;
	size_t y = floor(v.y - _offset.y) / _tileSize;
	
	size_t index = (y * _width) + x;
	return _tiles[index];
}

LevelSystem::TILE LevelSystem::getTile(sf::Vector2ul v) {
	
	size_t index = (v.y * _width) + v.x;
	return _tiles[index];
}

sf::Vector2f LevelSystem::getTilePosition(sf::Vector2ul v) {
	
	float xPos = (v.x * _tileSize) + _offset.x;
	float yPos = v.y * _tileSize + _offset.y;
	
	return {xPos, yPos};	
}

sf::Vector2f LevelSystem::getTileCentre(sf::Vector2ul v) {
	
	float xPos = v.x * _tileSize + _tileSize / 2 + _offset.x;
	float yPos = v.y * _tileSize + _tileSize / 2 + _offset.y;
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
	
	coords.x += _tileSize / 2 + _offset.x;
	coords.y += _tileSize / 2 + _offset.y;
	
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
 
sf::IntRect LevelSystem::getSpriteCoords(LevelSystem::TILE t) {
	auto it = _spriteCoords.find(t);
	if (it == _spriteCoords.end()) {
		_spriteCoords[t] = sf::IntRect(300,0,150,150);
	}
	return _spriteCoords[t];
}
 
 
void LevelSystem::setColor(LevelSystem::TILE t, sf::Color c) {
	_colours[t] = c;
}




void LevelSystem::loadLevel(const std::string &path, const std::string &sprites, sf::Vector2f windowSize) {
	
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
			case 'b':
				temp_tiles.push_back(BALL);
				break;
			case ' ':
				temp_tiles.push_back(EMPTY);
				break;
			case 'h':
				temp_tiles.push_back(HOLE);
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
	
	
	if (windowSize.x / w > windowSize.y / h) {
		_tileSize = windowSize.y / h;
		_offset = Vector2f((windowSize.x - _tileSize * w) / 2, 0);
	} else {
		_tileSize = windowSize.x / w;
		_offset = Vector2f(0, (windowSize.y - _tileSize * h) / 2);
	}
	
	
	
	cout << "Level " << path << " Loaded. " << w << "x" << h << std::endl;
	buildSprites(sprites);

}

void LevelSystem::buildSprites(const std::string &sprites) {
	
	_sprites.clear();
	
	texture.loadFromFile(sprites);
	
	for (size_t y = 0; y < LevelSystem::getHeight(); ++y) {
		for (size_t x = 0; x < LevelSystem::getWidth(); ++x) {
			
			auto s = make_unique<sf::RectangleShape>();
			
			s->setPosition(getTilePosition({x, y}));
			s->setSize(Vector2f(_tileSize, _tileSize));
			s->setFillColor(getColor(getTile({x, y})));
			s->setTexture(&texture);
			s->setTextureRect(getSpriteCoords(getTile({x, y})));
			
			
			_sprites.push_back(move(s)); 
			
			
		}
	}
}


		
void LevelSystem::render(RenderWindow &window) {
	for (size_t i = 0; i < _width * _height; ++i) {
		window.draw(*_sprites[i]);
	}
}


