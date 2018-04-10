
#include "scn_ui.h"

// ======================== UISCENE ======================== //
	


void UIScene::resize() {
	
}
	
void UIScene::load() {
	
	windowSize = (Vector2f)Renderer::getWindow().getSize();

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
	
	// line
	auto line = makeEntity();
	auto s = line->addComponent<ShapeComponent>();
	s->setShape<sf::RectangleShape>(sf::Vector2f(windowSize.x - 100, 2));
	s->getShape().setPosition(sf::Vector2f(windowSize.x / 2, sn->getText().getLocalBounds().height * 2));
	s->getShape().setFillColor(sf::Color(200 , 190, 183));
	s->getShape().setOrigin(Vector2f((windowSize.x - 100) / 2, 1));

	//testing audio component
	auto jukebox = makeEntity();
	auto audio = jukebox->addComponent<AudioComponent>();
	audio->LoadAudio("Enter_Press.wav");
	audio->PlayAudio();
	
}


