

#include "../game.h"

using namespace sf;
using namespace std;


const std::string controls[] = {
    "Left",
    "Right",
    "Up",
    "Down"
};


void RemapScene::update(const double& dt) {
	
	static double timer = 0.f;
	timer -= dt;
	
	if (timer < 0) {
	
		if (controlCount == 4) {
			
			if (!finished) {
				finish();
			}
				
			if ((Keyboard::isKeyPressed(Keyboard::B)) || (Joystick::isButtonPressed(0, 1))) //circle
			{
				auto jukebox = makeEntity();
				auto audio = jukebox->addComponent<AudioComponent>();
				audio->LoadAudio("Enter_Press.wav");
				audio->PlayAudio();
				while (audio->AudioIsPlaying())
				{
					//do nothing
				}
				Engine::changeScene(&menu);			
			}
			
		} else if (controlCount < Engine::controls.size()) {
			
			queryKey();
			controlCount = Engine::controls.size();
			
		}
		timer = 0.12f;
	}
		
}

void RemapScene::load() {
	
	UIScene::load();
	
	Engine::controls.clear();
	remapping = true;
	controlCount = 0;
	finished = false;
	
	
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
	
	
}

void RemapScene::unload() {
	
  _ents.list.clear();
	
	
}

void RemapScene::reload() {

}

void RemapScene::queryKey() {
	
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


