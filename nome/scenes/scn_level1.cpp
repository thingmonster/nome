#include "../game.h"
#include "scn_level1.h"


using namespace sf;
using namespace std;






std::shared_ptr<sf::Texture> Level1Scene::playerSprites;
std::shared_ptr<sf::Texture> Level1Scene::enemySprites;

void Level1Scene::update(const double& dt) {
		
	if (Keyboard::isKeyPressed(Keyboard::O)) {
		Engine::changeScene(&options);
	}
	
	if (Keyboard::isKeyPressed(Keyboard::P)) {
		Engine::changeScene(&paused);
	}
	
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		Engine::changeScene(&save);
	}
	
	if (Keyboard::isKeyPressed(Keyboard::L)) {
		Engine::changeScene(&loadGame);
	}
			

	static double timer = 1.0f;
	timer -= dt;
	if (timer < 0.f)  {
		if (maxEnemies > 0) {
			spawn();
			maxEnemies--;
		}
		timer = 4.f;
	}
	
	Scene::update(dt);
}

void Level1Scene::render() {
	ls::render(Renderer::getWindow());
	Scene::render();
}

void Level1Scene::unload() {
}
	
void Level1Scene::restore(std::vector<std::shared_ptr<Entity>> entities) {
	
	if (ls::findTiles(ls::EMPTY).size() == 0) {
		sf::Vector2f windowSize = (Vector2f)Renderer::getWindow().getSize();
		ls::loadLevel("res/levels/level1.txt", "res/sprites/level1.png", windowSize);
		playerSprites = Resources::get<sf::Texture>("player.png");
		enemySprites = Resources::get<sf::Texture>("beetles-black.png");
	}
	
	
	player = entities[0];
	makePlayer(player);
	
	ball = entities[1];
	makeBall(ball);
	
	for (int i = 2; i < entities.size(); ++i) {
		makeEnemy(entities[i]);
	}
	
	for (auto& e : entities) {
		_ents.list.push_back(e);
	}
	cout << _ents.list.size() << endl;
}
	
void Level1Scene::makePlayer(std::shared_ptr<Entity> player) {
	
	auto s = player->addComponent<ShapeComponent>();
	s->setShape<sf::CircleShape>(20.f);
	s->getShape().setFillColor({255 , 255, 255});
	s->getShape().setOrigin(Vector2f(20.f, 20.f));
	s->setTexture(playerSprites, sf::IntRect(0,0,50,50));
	auto m = player->addComponent<PlayerMovementComponent>();
	m->setSpeed(200.f);
		
}

void Level1Scene::makeBall(std::shared_ptr<Entity> ball) {
	
	auto b = ball->addComponent<ShapeComponent>();
	b->setShape<sf::CircleShape>(20.f);
	b->getShape().setFillColor({255 , 255, 255});
	b->getShape().setOrigin(Vector2f(20.f, 20.f));
	b->setTexture(playerSprites, sf::IntRect(50,0,50,50));
	// add ball movement component here?
	
}

void Level1Scene::makeEnemy(std::shared_ptr<Entity> enemy) {
	
	sf::Vector2f windowSize = (Vector2f)Renderer::getWindow().getSize();
	
	auto shape = enemy->addComponent<ShapeComponent>();
	shape->setShape<sf::CircleShape>(20.f);
	shape->getShape().setFillColor({255 , 255, 255});
	shape->getShape().setOrigin(Vector2f(20.f, 20.f));
	shape->setTexture(enemySprites, sf::IntRect(0,0,50,50));
	
	/* // steering component
	auto move = enemy->addComponent<SteeringComponent>(player.get()); */
	
	/* // pathfinding component
	// auto path = pathFind(Vector2i(1, 1), Vector2i(ls::getWidth() - 2, ls::getHeight() - 2));
	// auto move = enemy->addComponent<PathfindingComponent>();
	// move->setPath(path); */
	
	/* // state machine component
	auto sm = enemy->addComponent<StateMachineComponent>();
	sm->addState("normal", make_shared<NormalState>(player));
	sm->addState("near", make_shared<NearState>(player));
	sm->changeState("normal"); */
	
	
	// decision tree component
	random_device dev;
	default_random_engine engine(dev());
	uniform_real_distribution<float> x_dist(0.0f, windowSize.x);
	uniform_real_distribution<float> y_dist(0.0f, windowSize.y);
	
	auto decision = make_shared<DistanceDecision>(
		player,
		50.f,
		make_shared<FleeDecision>(),
		make_shared<DistanceDecision>(
			player,
			100.f,
			make_shared<RandomDecision> (
				make_shared<SeekDecision>(),
				make_shared<StationaryDecision>()
			),
			make_shared<SeekDecision>()
		)
	);
	
	enemy->addComponent<DecisionTreeComponent>(decision);
	
	auto sm = enemy->addComponent<StateMachineComponent>();
	sm->addState("stationary", make_shared<StationaryState>());
	sm->addState("seek", make_shared<SeekState>(enemy, player));
	sm->addState("flee", make_shared<FleeState>(enemy, player));
	
	
}

void Level1Scene::load() {
	
	if (!loaded) {
			
		Engine::changeLevel(&level1);
		
		sf::Vector2f windowSize = (Vector2f)Renderer::getWindow().getSize();
		
		ls::loadLevel("res/levels/level1.txt", "res/sprites/level1.png", windowSize);
		
		playerSprites = Resources::get<sf::Texture>("player.png");
		enemySprites = Resources::get<sf::Texture>("beetles-black.png");
		
		
		player = Level1Scene::makeEntity();
		player->setPosition(ls::getTileCentre(ls::findTiles(ls::START)[0]));
		makePlayer(player);
		
		// auto s = player->addComponent<ShapeComponent>();
		// s->setShape<sf::CircleShape>(20.f);
		// s->getShape().setFillColor({255 , 255, 255});
		// s->getShape().setOrigin(Vector2f(20.f, 20.f));
		// s->setTexture(playerSprites, sf::IntRect(0,0,50,50));
		// auto m = player->addComponent<PlayerMovementComponent>();
		// m->setSpeed(200.f);
		
		ball = Level1Scene::makeEntity();
		ball->setPosition(ls::getTileCentre(ls::findTiles(ls::BALL)[0]));
		makeBall(ball);
		
		// auto b = ball->addComponent<ShapeComponent>();
		// b->setShape<sf::CircleShape>(20.f);
		// b->getShape().setFillColor({255 , 255, 255});
		// b->getShape().setOrigin(Vector2f(20.f, 20.f));
		// b->setTexture(playerSprites, sf::IntRect(50,0,50,50));
		// add ball movement component here?
		
		loaded = true;
	}
}

void Level1Scene::reload() {
	
}

void Level1Scene::spawn() {
	
	auto entity = Level1Scene::makeEntity();
	entity->setPosition(ls::getTileCentre(ls::findTiles(ls::HOLE)[0]));
	makeEnemy(entity);
}





