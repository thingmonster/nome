#pragma once
#include "engine.h"
#include "../components/cmp_text.h"
#include "../components/cmp_shape.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

class UIScene : public Scene {
		
	public:
		UIScene() = default;
		virtual void update(const double& dt) = 0;
		virtual void unload() = 0;
		virtual void reload() = 0;
		void load();
		void resize();
		

	
};
