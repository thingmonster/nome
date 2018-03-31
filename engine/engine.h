#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>


class Engine {
	
	public:
		Engine() = delete;
		~Engine() = delete;
		static void Start(int width, int height, const std::string& name);
		
};
