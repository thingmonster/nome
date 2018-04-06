
#include "scn_remap.h"
#include "../components/cmp_text.h"
#include "../components/cmp_shape.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace sf;
using namespace std;


const std::string controls[] = {
    "Left",
    "Right",
    "Up",
    "Down"
};


void RemapScene::update(const double& dt) {
	
	if (controlCount == 4) {
		
		if (!finished) {
			finish();
		}
			
		if (Keyboard::isKeyPressed(Keyboard::B)) {
			Engine::changeScene(&menu);			
		}
		
	} else if (controlCount < Engine::controls.size()) {
		
		queryKey();
		controlCount = Engine::controls.size();
		
	}
	
}

void RemapScene::load() {
	
	Engine::controls.clear();
	remapping = true;
	controlCount = 0;
	finished = false;
	
	sf::Vector2f windowSize = (Vector2f)Renderer::getWindow().getSize();

	// background	
	auto background = makeEntity();
	auto b = background->addComponent<ShapeComponent>();
	b->setShape<sf::RectangleShape>(sf::Vector2f(windowSize.x, windowSize.y));
	b->getShape().setPosition(sf::Vector2f(0,0));
	b->getShape().setFillColor(sf::Color(72,62,55));
	
	// "story of nome"
	auto son = makeEntity();
	auto sn = son->addComponent<TextComponent>("The Story of Nome", "WorstveldSling.ttf");
	sn->setColor(sf::Color(200 , 190, 183));
	sn->setCharacterSize(75);
	sn->SetPosition({windowSize.x / 2 - sn->getText().getLocalBounds().width / 2, 10});
	
	
	// ============================== CONTENT ============================== // 
	
	// "Remap Controls"
	auto rm = makeEntity();
	auto rM = rm->addComponent<TextComponent>("Remap Controls", "Rubik-Medium.ttf");
	rM->setColor(sf::Color(200 , 190, 183));
	rM->setCharacterSize(50);
	rM->SetPosition({windowSize.x / 2 - rM->getText().getLocalBounds().width / 2, 150});
	
	// choose keys
	instructions = makeEntity();
	auto i = instructions->addComponent<TextComponent>("Choose a Key to Move " + controls[controlCount], "Rubik-Medium.ttf");
	i->setColor(sf::Color(200 , 190, 183));
	i->setCharacterSize(25);
	i->SetPosition({windowSize.x / 2 - i->getText().getLocalBounds().width / 2, 225});
	
	// ============================== FOOT ============================== // 
	
	// line
	auto line = makeEntity();
	auto s = line->addComponent<ShapeComponent>();
	s->setShape<sf::RectangleShape>(sf::Vector2f(windowSize.x - 100, 2));
	s->getShape().setPosition(sf::Vector2f(windowSize.x / 2, sn->getText().getLocalBounds().height * 2));
	s->getShape().setFillColor(sf::Color(200 , 190, 183));
	s->getShape().setOrigin(Vector2f((windowSize.x - 100) / 2, 1));
	
	
}

void RemapScene::unload() {
	
  _ents.list.clear();
	
	
}

void RemapScene::reload() {

}

void RemapScene::queryKey() {
	
	sf::Vector2f windowSize = (Vector2f)Renderer::getWindow().getSize();

	auto entity = makeEntity();
	auto text = entity->addComponent<TextComponent>(controls[controlCount], "Rubik-Medium.ttf");
	text->setColor(sf::Color(200, 190, 183));
	text->setCharacterSize(25);
	text->SetPosition({
		windowSize.x / 2 - text->getText().getLocalBounds().width, 
		(windowSize.y / 2 - 20) + (45 * controlCount)
	});

	
	auto newKey = makeEntity();
	auto keyText = newKey->addComponent<TextComponent>(Engine::keyStrings[Engine::controls[controlCount]], "Rubik-Medium.ttf");
	keyText->setColor(sf::Color(72,62,55));
	keyText->setCharacterSize(25);
	keyText->SetPosition({
		windowSize.x / 2 + 30, 
		(windowSize.y / 2 - 20) + (45 * controlCount)
	});

	Vector2f bounds(keyText->getText().getLocalBounds().width, 35);
	
	float positionOffset = 0;
	if (bounds.x < 20) {
		positionOffset = (20 - bounds.x) / 2;
	}
	
	IntRect textureRect(0,0,40,40);
	if (bounds.x > 80) {
		textureRect = IntRect(40,0,80,40);
	}
	
	if (bounds.x < 20) {
		bounds.x = 40;
	} else {
		bounds.x += 20;
	}
	
	keyText->SetPosition({
		windowSize.x / 2 + 30 + positionOffset, 
		(windowSize.y / 2 - 20) + (45 * controlCount)
	});
	
	
	
	std::shared_ptr<sf::Texture> keySprites = Resources::get<sf::Texture>("ui_key.png");
	
	auto background = makeEntity();
	auto bg = background->addComponent<ShapeComponent>();
	bg->setShape<sf::RectangleShape>(bounds);
	// bg->getShape().setOrigin(20,20);
	bg->getShape().setFillColor(sf::Color(255,255,255));
	bg->setTexture(keySprites, textureRect);
	bg->getShape().setPosition({
		windowSize.x / 2 + 20, 
		(windowSize.y / 2 - 20) + (45 * controlCount)
	});
	
	iter_swap(_ents.list.begin() + _ents.list.size() - 2, _ents.list.begin() + _ents.list.size() - 1);
	
	if (controlCount < 3) {
		auto i = instructions->getComponents<TextComponent>();
		i[0]->setString("Choose a Key to Move "+controls[controlCount + 1]);
	}
}



void RemapScene::finish() {
	
	sf::Vector2f windowSize = (Vector2f)Renderer::getWindow().getSize();

	// "press enter to begin"
	auto petb = makeEntity();
	auto pe = petb->addComponent<TextComponent>("Finished - press B to go back to options screen", "WorstveldSling.ttf");
	pe->setColor(sf::Color(200 , 190, 183));
	pe->setCharacterSize(50);
	pe->SetPosition({
		windowSize.x / 2 - pe->getText().getLocalBounds().width / 2, 
		windowSize.y - 85
	});
	
	// line
	auto line2 = makeEntity();
	auto s2 = line2->addComponent<ShapeComponent>();
	s2->setShape<sf::RectangleShape>(sf::Vector2f(windowSize.x - 100, 2));
	s2->getShape().setPosition(sf::Vector2f(windowSize.x / 2, windowSize.y - 100));
	s2->getShape().setFillColor(sf::Color(200 , 190, 183));
	s2->getShape().setOrigin(Vector2f((windowSize.x - 100) / 2, 1));
	
	instructions->setVisible(false);
	finished = true;
	
}


