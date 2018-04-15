

#include "../game.h"

using namespace sf;
using namespace std;

// labels for the controls functionality
const std::string controls[] = {
    "Left",
    "Right",
    "Up",
    "Down"
};


void RemapScene::update(const double& dt) {
	
	// prevent single keypresses being registered as multiple events
	static double timer = 0.f;
	timer -= dt;
	
	if (timer < 0) {
	
		// if four controls have already been submitted
		if (controlCount == 4) {
			
			if (!finished) {
				finish();
			}
			
			// if game is in progress resume, else go to start menu
			if ((Keyboard::isKeyPressed(Keyboard::Tab)) || (Joystick::isButtonPressed(0, 1))) //circle
			{
				auto jukebox = makeEntity();
				auto audio = jukebox->addComponent<AudioComponent>();
				audio->LoadAudio("Enter_Press.wav");
				audio->PlayAudio();
				while (audio->AudioIsPlaying())
				{
					//do nothing
				}
				if (Engine::getLevel() == nullptr) {
					Engine::changeScene(&menu);
				} else {
					Engine::changeScene(Engine::getLevel());
				}
							
			}
			
		} 
		
		// still waiting for all the controls to be submitted
		else if (controlCount < Engine::controls.size()) {
			
			// set up for the next control to be submitted
			queryKey();
			
			// update controls count to match engine
			controlCount = Engine::controls.size();
			
		}
		timer = 0.12f;
	}
		
}

void RemapScene::load() {
	
	// create top section
	UIScene::load();
	
	// empty the controls array, set flags and reset counter
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
	
	// create the text description for the newly submitted key
	auto entity = makeEntity();
	auto text = entity->addComponent<TextComponent>(controls[controlCount], "Rubik-Medium.ttf");
	text->setColor(sf::Color(200, 190, 183));
	text->setCharacterSize(25);
	text->SetPosition({
		windowSize.x / 2 - text->getText().getLocalBounds().width, 
		(windowSize.y / 2 - 20) + (45 * controlCount)
	});

	// create text for the newly submitted key
	auto newKey = makeEntity();
	auto keyText = newKey->addComponent<TextComponent>(Engine::keyStrings[Engine::controls[controlCount]], "Rubik-Medium.ttf");
	keyText->setColor(sf::Color(72,62,55));
	keyText->setCharacterSize(25);
	keyText->SetPosition({
		windowSize.x / 2 + 30, 
		(windowSize.y / 2 - 20) + (45 * controlCount)
	});

	// get text bounds and use to determine size and position of background
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
	
	
	// load background and create entity in front of key text
	std::shared_ptr<sf::Texture> keySprites = Resources::get<sf::Texture>("ui_key.png");
	
	auto background = makeEntity();
	auto bg = background->addComponent<ShapeComponent>();
	bg->setShape<sf::RectangleShape>(bounds);
	bg->getShape().setFillColor(sf::Color(255,255,255));
	bg->setTexture(keySprites, textureRect);
	bg->getShape().setPosition({
		windowSize.x / 2 + 20, 
		(windowSize.y / 2 - 20) + (45 * controlCount)
	});
	
	// move background behind key text
	iter_swap(_ents.list.begin() + _ents.list.size() - 2, _ents.list.begin() + _ents.list.size() - 1);
	
	// if there are still some controls to go show the next message
	if (controlCount < 3) {
		auto i = instructions->getComponents<TextComponent>();
		i[0]->setString("Choose a Key to Move "+controls[controlCount + 1]);
	}
}



void RemapScene::finish() {
	
	// all controls have been submitted
	
	sf::Vector2f windowSize = (Vector2f)Renderer::getWindow().getSize();

	// check if game is in progress for customised "finished" text
	
	std::string backText;
	if (Engine::getLevel() == nullptr) {
		backText = "Press TAB to go back";
	} else {
		backText = "Press TAB to resume game";
	}
	auto petb = makeEntity();
	auto pe = petb->addComponent<TextComponent>("Finished - "+backText, "WorstveldSling.ttf");
	pe->setColor(sf::Color(200 , 190, 183));
	pe->setCharacterSize(40);
	pe->SetPosition({
		windowSize.x / 2 - pe->getText().getLocalBounds().width / 2, 
		windowSize.y - 85
	});
	
	// footer divider
	auto footDivider = makeEntity();
	auto divider = footDivider->addComponent<ShapeComponent>();
	divider->setShape<sf::RectangleShape>(sf::Vector2f(windowSize.x - 100, 2));
	divider->getShape().setPosition(sf::Vector2f(windowSize.x / 2, windowSize.y - 100));
	divider->getShape().setFillColor(sf::Color(200 , 190, 183));
	divider->getShape().setOrigin(Vector2f((windowSize.x - 100) / 2, 1));
	
	// hide instructions set set finished flag
	instructions->setVisible(false);
	finished = true;
	
}


