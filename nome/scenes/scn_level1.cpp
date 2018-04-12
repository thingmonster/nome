#include "../game.h"
#include "scn_level1.h"


using namespace sf;
using namespace std;


std::shared_ptr<sf::Texture> Level1Scene::playerSprites;
std::shared_ptr<sf::Texture> Level1Scene::enemySprites;

void Level1Scene::update(const double& dt) {
	
	if ((Keyboard::isKeyPressed(Keyboard::O)) || (Joystick::isButtonPressed(0, 6))) //select
	{
		auto jukebox = makeEntity();
		auto audio = jukebox->addComponent<AudioComponent>();
		audio->LoadAudio("Enter_Press.wav");
		audio->PlayAudio();
		while (audio->AudioIsPlaying())
		{
			//do nothing
		}
		Engine::changeScene(&options);
	}
	
	if ((Keyboard::isKeyPressed(Keyboard::P)) || (Joystick::isButtonPressed(0, 1))) //circle
	{
		auto jukebox = makeEntity();
		auto audio = jukebox->addComponent<AudioComponent>();
		audio->LoadAudio("Enter_Press.wav");
		audio->PlayAudio();
		while (audio->AudioIsPlaying())
		{
			//do nothing
		}
		Engine::changeScene(&paused);
	}

	if ((Keyboard::isKeyPressed(Keyboard::S)) || (Joystick::isButtonPressed(0, 2))) //square
	{
		auto jukebox = makeEntity();
		auto audio = jukebox->addComponent<AudioComponent>();
		audio->LoadAudio("Enter_Press.wav");
		audio->PlayAudio();
		while (audio->AudioIsPlaying())
		{
			//do nothing
		}
		Engine::changeScene(&save);
	}
	
	if ((Keyboard::isKeyPressed(Keyboard::L)) || (Joystick::isButtonPressed(0, 3))) //triangle
	{
		auto jukebox = makeEntity();
		auto audio = jukebox->addComponent<AudioComponent>();
		audio->LoadAudio("Enter_Press.wav");
		audio->PlayAudio();
		while (audio->AudioIsPlaying())
		{
			//do nothing
		}
		Engine::changeScene(&loadGame);
	}
			

	int beetles = 0;
	for (auto &e : _ents.list) {
		if (e->getTag() == "beetle") {
			beetles++;
		}
	}
	
	static double timer = 1.0f;
	timer -= dt;
	if (timer < 0.f)  {
		if (maxEnemies > beetles) {
			spawn();
		}
		timer = 5.f;
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
		updateEnemyAI(entities[i]);
	}
	
	for (auto& e : entities) {
		_ents.list.push_back(e);
	}
	
}
	
void Level1Scene::makePlayer(std::shared_ptr<Entity> player) {
	
	auto checkShapes = player->getComponents<ShapeComponent>();
	if (checkShapes.size() == 0) {
		player->addComponent<ShapeComponent>();
	}
	auto shape = player->getComponents<ShapeComponent>();
	
	shape[0]->setShape<sf::CircleShape>(ls::getTileSize() / 3);
	shape[0]->getShape().setFillColor({255 , 255, 255});
	shape[0]->getShape().setOrigin(Vector2f(ls::getTileSize() / 3, ls::getTileSize() / 3));
	shape[0]->setTexture(playerSprites, sf::IntRect(0,0,50,50));
	
	auto p = player->addComponent<PlayerPhysicsComponent>(Vector2f(ls::getTileSize() / 3, ls::getTileSize() / 3));
	
}

void Level1Scene::makeBall(std::shared_ptr<Entity> ball) {
	
	auto checkShapes = ball->getComponents<ShapeComponent>();
	if (checkShapes.size() == 0) {
		ball->addComponent<ShapeComponent>();
	}
	
	auto shape = ball->getComponents<ShapeComponent>();
	shape[0]->setShape<sf::CircleShape>(ls::getTileSize() / 4);
	shape[0]->getShape().setFillColor({255 , 255, 255});
	shape[0]->getShape().setOrigin(Vector2f(ls::getTileSize() / 4, ls::getTileSize() / 4));
	shape[0]->setTexture(playerSprites, sf::IntRect(50,0,50,50));

	auto physics = ball->addComponent<PhysicsComponent>(true, Vector2f(ls::getTileSize() / 4, ls::getTileSize() / 4));
	
	
}

void Level1Scene::makeEnemy(std::shared_ptr<Entity> enemy) {
	
	auto checkShapes = enemy->getComponents<ShapeComponent>();
	if (checkShapes.size() == 0) {
		enemy->addComponent<ShapeComponent>();
	}
	
	auto shape = enemy->getComponents<ShapeComponent>();
	shape[0]->setShape<sf::CircleShape>(ls::getTileSize() / 4);
	shape[0]->getShape().setFillColor({255 , 255, 255});
	shape[0]->getShape().setOrigin(Vector2f(ls::getTileSize() / 4, ls::getTileSize() / 4));
	shape[0]->setTexture(enemySprites, sf::IntRect(0,0,50,50));
	
	auto checkMovement = enemy->getComponents<MovementComponent>();
	if (checkMovement.size() == 0) {
		enemy->addComponent<MovementComponent>();
	}
	
}

void Level1Scene::load() {
	
	if (!loaded) {
			
		Engine::changeLevel(&level1);
		windowSize = (Vector2f)Renderer::getWindow().getSize();
		ls::loadLevel("res/levels/level1.txt", "res/sprites/level1.png", windowSize);
		
		
    auto walls = ls::findTiles(ls::WALL);
    for (auto w : walls) {
			auto pos = ls::getTilePosition(w);
			pos += Vector2f(ls::getTileSize() / 2, ls::getTileSize() / 2); 
			auto e = makeEntity("wall");
			e->setPosition(pos);
			e->addComponent<PhysicsComponent>(false, Vector2f(ls::getTileSize(), ls::getTileSize()));
    }
		
		
		playerSprites = Resources::get<sf::Texture>("player.png");
		enemySprites = Resources::get<sf::Texture>("beetles-black.png");
		
		player = Level1Scene::makeEntity("player");
		player->setPosition(ls::getTileCentre(ls::findTiles(ls::START)[0]));
		makePlayer(player);
		
		ball = Level1Scene::makeEntity("ball");
		ball->setPosition(ls::getTileCentre(ls::findTiles(ls::BALL)[0]));
		makeBall(ball);
		
		loaded = true;
	}
}

void Level1Scene::reload() {
	
}

void Level1Scene::spawn() {
	auto jukebox = makeEntity();
	auto audio = jukebox->addComponent<AudioComponent>();
	audio->LoadAudio("Beetle_Walking.wav");
	audio->PlayAudio();
	auto entity = Level1Scene::makeEntity("beetle");
	entity->setPosition(ls::getTileCentre(ls::findTiles(ls::HOLE)[0]));
	makeEnemy(entity);
	addEnemyAI(entity);
	
	auto physics = entity->addComponent<EnemyPhysicsComponent>(Vector2f(ls::getTileSize() / 4, ls::getTileSize() / 4));
	
}

void Level1Scene::resize() {
	
	// get current player position
	Vector2f pPos(
		(player->getPosition().x - ls::getOffset().x) / (ls::getWidth() * ls::getTileSize()),
		(player->getPosition().y - ls::getOffset().y) / (ls::getHeight() * ls::getTileSize())
	);
	
	// get current ball position
	Vector2f bPos(
		(ball->getPosition().x - ls::getOffset().x) / (ls::getWidth() * ls::getTileSize()),
		(ball->getPosition().y - ls::getOffset().y) / (ls::getHeight() * ls::getTileSize())
	);
	
	// get current enemy positions
	
	std::vector<sf::Vector2f> ePos;
	
	for(int i = 2; i < _ents.list.size(); ++i) {
		ePos.push_back(sf::Vector2f(
			(_ents.list[i]->getPosition().x - ls::getOffset().x) / (ls::getWidth() * ls::getTileSize()),
			(_ents.list[i]->getPosition().y - ls::getOffset().y) / (ls::getHeight() * ls::getTileSize())
		));
	}
	
	// resize level system
	windowSize = (Vector2f)Renderer::getWindow().getSize();
	if (ls::findTiles(ls::EMPTY).size() > 0) {
		ls::resize("res/sprites/level1.png", windowSize);
	}
	
	// move and restyle player
	player->setPosition(Vector2f(
		(pPos.x * (ls::getWidth() * ls::getTileSize())) + ls::getOffset().x,
		(pPos.y * (ls::getHeight() * ls::getTileSize())) + ls::getOffset().y
	));
	makePlayer(player);
	
	// move and restyle ball
	ball->setPosition(Vector2f(
		(bPos.x * (ls::getWidth() * ls::getTileSize())) + ls::getOffset().x,
		(bPos.y * (ls::getHeight() * ls::getTileSize())) + ls::getOffset().y
	));
	makeBall(ball);
	
	// move and restyle enemies
	
	for(int i = 2; i < _ents.list.size(); ++i) {
		_ents.list[i]->setPosition(Vector2f(
			(ePos[i-2].x * (ls::getWidth() * ls::getTileSize())) + ls::getOffset().x,
			(ePos[i-2].y * (ls::getHeight() * ls::getTileSize())) + ls::getOffset().y
		));
		makeEnemy(_ents.list[i]);
		updateEnemyAI(_ents.list[i]);
	}
	
	
	
}


void Level1Scene::addEnemyAI(std::shared_ptr<Entity> enemy) {
	
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
	
	auto decision = decisionTree();
	enemy->addComponent<DecisionTreeComponent>(decision);
	
	auto sm = enemy->addComponent<StateMachineComponent>();
	sm->addState("stationary", make_shared<StationaryState>());
	sm->addState("seek", make_shared<SeekState>(enemy, player, ls::getTileSize() / 75));
	sm->addState("flee", make_shared<FleeState>(enemy, player, ls::getTileSize() / 75));
	sm->addState("wander", make_shared<WanderState>(enemy, player, ls::getTileSize() / 75));
	
	
	
}

void Level1Scene::updateEnemyAI(std::shared_ptr<Entity> enemy) {
	
	auto decision = decisionTree();
	
	auto checkForTree = enemy->getComponents<DecisionTreeComponent>();
	if (checkForTree.size() == 0) {
		enemy->addComponent<DecisionTreeComponent>(decision);
	} else {
		auto dt = enemy->getComponents<DecisionTreeComponent>();
		dt[0]->setDecisionTree(decision);
	}
	
	auto checkForStateMachine = enemy->getComponents<StateMachineComponent>();
	if (checkForStateMachine.size() == 0) {
		enemy->addComponent<StateMachineComponent>();
	}
	
	auto sm = enemy->getComponents<StateMachineComponent>();
	sm[0]->removeState("stationary");
	sm[0]->removeState("seek");
	sm[0]->removeState("flee");
	sm[0]->removeState("wander");
	sm[0]->addState("stationary", make_shared<StationaryState>());
	sm[0]->addState("seek", make_shared<SeekState>(enemy, player, ls::getTileSize() / 75));
	sm[0]->addState("flee", make_shared<FleeState>(enemy, player, ls::getTileSize() / 75));
	sm[0]->addState("wander", make_shared<WanderState>(enemy, player, ls::getTileSize() / 75));
	
	
	
}

std::shared_ptr<DistanceDecision> Level1Scene::decisionTree() {
	
	auto decision = make_shared<DistanceDecision>(
		player,
		ls::getTileSize() * 1,
		make_shared<FleeDecision>(),
		make_shared<DistanceDecision>(
			player,
			ls::getTileSize() * 3,
			// make_shared<DistanceDecision> (
				// player,
				// ls::getTileSize() * 4,
				// make_shared<SeekDecision>(),
				// make_shared<StationaryDecision>()
			// ),
			make_shared<WanderDecision>(),
			make_shared<WanderDecision>()
		)
	);
	
	return decision;
}













