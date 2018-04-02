#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>
#include "maths.h"

#define ls LevelSystem


class LevelSystem {
	
	public:
		enum TILE {EMPTY, START, BALL, WALL, HOLE};
		static void loadLevel(const std::string& path, const std::string& sprites, sf::Vector2f windowSize = {800.f, 600.f});
		static void render(sf::RenderWindow &window);
		
		static sf::IntRect getSpriteCoords(TILE t);
		static sf::Color getColor(TILE t);
		static void setColor(TILE t, sf::Color c);
		static sf::Texture texture;
		
		static size_t getWidth();
		static size_t getHeight();
		static float getTileSize();
		static sf::Vector2ul screenCoordsToIndexes(sf::Vector2f);
		
		static TILE getTile(sf::Vector2ul v);
		static TILE getTileAt(sf::Vector2f);
		static TILE getTileFromScreenCoords(sf::Vector2f);
		static sf::Vector2f getTilePosition(sf::Vector2ul v);
		static sf::Vector2f getTileCentre(sf::Vector2ul v);
		
		static std::vector<sf::Vector2ul> findTiles(TILE t);
		static sf::Vector2f getTileCoordinates(TILE t);
		

		
		
	protected:
		static std::unique_ptr<TILE[]> _tiles;
		static std::map<TILE, sf::Color> _colours;
		static std::map<TILE, sf::IntRect> _spriteCoords;
		static size_t _width;
		static size_t _height;
		static float _tileSize;
		static std::vector<std::unique_ptr<sf::RectangleShape>> _sprites;
		static void buildSprites(const std::string&);

		
		
		
	private:
		LevelSystem() = delete;
		~LevelSystem() = delete;
		
	 
};
		




		