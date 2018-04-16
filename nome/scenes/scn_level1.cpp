#include "../game.h"
#include "scn_level1.h"


using namespace sf;
using namespace std;


std::shared_ptr<sf::Texture> Level1Scene::playerSprites;
std::shared_ptr<sf::Texture> Level1Scene::enemySprites;



void Level1Scene::update(const double& dt) {
	
	// go to options scene
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
	
	// go to paused scene
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

	// go to save game scene
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
	
	// go to load game scene
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
			

	// add a new beetle every few seconds until maximum beetles are reached
	
	// count beetles
	int beetles = 0;
	for (auto &e : _ents.list) {
		if (e->getTag() == "beetle") {
			beetles++;
		}
	}
	
	// and maybe add a beetle
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

void Level1Scene::load() {
	
	/* 
	
	resources and loaded and player, ball and 
	wall entities are created here
	
	*/
	
	if (!loaded) {
			
		// set as active level
		Engine::changeLevel(&level1);
		
		// get window size
		windowSize = (Vector2f)Renderer::getWindow().getSize();
		
		// load map
		ls::loadLevel("res/levels/level1.txt", "res/sprites/level1.png", windowSize);
		
		// load graphics
		playerSprites = Resources::get<sf::Texture>("player.png");
		enemySprites = Resources::get<sf::Texture>("beetles-black.png");
		
		// set up box2d bodies for the walls
    auto walls = ls::findTiles(ls::WALL);
    for (auto w : walls) {
			auto pos = ls::getTilePosition(w);
			pos += Vector2f(ls::getTileSize() / 2, ls::getTileSize() / 2); 
			auto e = makeEntity("wall");
			e->setPosition(pos);
			e->addComponent<PhysicsComponent>(false, Vector2f(ls::getTileSize(), ls::getTileSize()));
    }
		
		// make player entity
		player = Level1Scene::makeEntity("player");
		player->setPosition(ls::getTileCentre(ls::findTiles(ls::START)[0]));
		makePlayer(player);
		
		// make ball entity
		ball = Level1Scene::makeEntity("ball");
		ball->setPosition(ls::getTileCentre(ls::findTiles(ls::BALL)[0]));
		makeBall(ball);
		
		auto jukebox = makeEntity();
		auto music = jukebox->addComponent<AudioComponent>();
		music->LoadMusic("nome_game.flac");
		music->PlayMusic();

		loaded = true;
	}
}

void Level1Scene::unload() {
}
	
void Level1Scene::reload() {
	
}

	
	
/* load level from saved file */

void Level1Scene::restore(std::vector<std::shared_ptr<Entity>> entities) {
	
	// load map and graphics and get current window size if necessary
	if (ls::findTiles(ls::EMPTY).size() == 0) {
		sf::Vector2f windowSize = (Vector2f)Renderer::getWindow().getSize();
		ls::loadLevel("res/levels/level1.txt", "res/sprites/level1.png", windowSize);
		playerSprites = Resources::get<sf::Texture>("player.png");
		enemySprites = Resources::get<sf::Texture>("beetles-black.png");
	}
	
	// for each entity in the file...
	for (auto& e : entities) {
		
		// multiply the position by tile size and add map offset
		Vector2f pos = Vector2f(
			(e->getPosition().x * (ls::getWidth() * ls::getTileSize())) + ls::getOffset().x,
			(e->getPosition().y * (ls::getHeight() * ls::getTileSize())) + ls::getOffset().y
		);
		
		// if it's a player create a player
		if (e->getTag() == "player") {
			player = e;
			player->setPosition(pos);
			makePlayer(player);
		}
		
		// if it's a ball create a ball
		if (e->getTag() == "ball") {
			ball = e;
			ball->setPosition(Vector2f(pos));
			makeBall(ball);
		}
		
		// if it's a beetle create a beetle
		if (e->getTag() == "beetle") {
			e->setPosition(Vector2f(pos));
			makeEnemy(e);
			updateEnemyAI(e);
		}
		
		// if it's a wall create a physics body
		if (e->getTag() == "wall") {	
			e->setPosition(pos);
			e->addComponent<PhysicsComponent>(false, Vector2f(ls::getTileSize(), ls::getTileSize()));
		}
	}
	
	// and add them all to the entity manager
	for (auto& e : entities) {
		_ents.list.push_back(e);
	}
	
}


/* resize level if window has been changed from UI or manually */

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
	std::vector<std::shared_ptr<Entity>> beetles;
	
	for(int i = 2; i < _ents.list.size(); ++i) {
		if (_ents.list[i]->getTag() == "beetle") {
			ePos.push_back(sf::Vector2f(
				(_ents.list[i]->getPosition().x - ls::getOffset().x) / (ls::getWidth() * ls::getTileSize()),
				(_ents.list[i]->getPosition().y - ls::getOffset().y) / (ls::getHeight() * ls::getTileSize())
			));
			beetles.push_back(_ents.list[i]);
		}
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
	for(int i = 0; i < beetles.size(); ++i) {
		beetles[i]->setPosition(Vector2f(
			(ePos[i].x * (ls::getWidth() * ls::getTileSize())) + ls::getOffset().x,
			(ePos[i].y * (ls::getHeight() * ls::getTileSize())) + ls::getOffset().y
		));
		makeEnemy(beetles[i]);
		updateEnemyAI(beetles[i]);
	}
	
	
	
}

	
/* add characteristics and components to existing entities */
	
void Level1Scene::makePlayer(std::shared_ptr<Entity> player) {
	
	// add shape component if not present
	auto checkShapes = player->getComponents<ShapeComponent>();
	if (checkShapes.size() == 0) {
		player->addComponent<ShapeComponent>();
	}
	
	// set size, origin, texture etc
	auto shape = player->getComponents<ShapeComponent>();
	shape[0]->setShape<sf::CircleShape>(ls::getTileSize() / 3);
	shape[0]->getShape().setFillColor({255 , 255, 255});
	shape[0]->getShape().setOrigin(Vector2f(ls::getTileSize() / 3, ls::getTileSize() / 3));
	shape[0]->setTexture(playerSprites, sf::IntRect(0,0,300,300));
	
	
	// add physics component if not present
	auto checkPhysics = player->getComponents<PhysicsComponent>();
	if (checkPhysics.size() == 0) {
		player->addComponent<PlayerPhysicsComponent>(
			Vector2f(ls::getTileSize() / 3, ls::getTileSize() / 3),
			ls::getTileSize() / 1.1
		);
	}
}

void Level1Scene::makeBall(std::shared_ptr<Entity> ball) {
	
	// add shape component if not present
	auto checkShapes = ball->getComponents<ShapeComponent>();
	if (checkShapes.size() == 0) {
		ball->addComponent<ShapeComponent>();
	}
	
	// set size, origin, texture etc
	auto shape = ball->getComponents<ShapeComponent>();
	shape[0]->setShape<sf::CircleShape>(ls::getTileSize() / 4);
	shape[0]->getShape().setFillColor({255 , 255, 255});
	shape[0]->getShape().setOrigin(Vector2f(ls::getTileSize() / 4, ls::getTileSize() / 4));
	shape[0]->setTexture(playerSprites, sf::IntRect(300,0,300,300));
	
	// add physics component if not present
	auto checkPhysics = ball->getComponents<BallPhysicsComponent>();
	if (checkPhysics.size() == 0) {
		ball->addComponent<BallPhysicsComponent>(Vector2f(ls::getTileSize() / 4, ls::getTileSize() / 4), ls::getTileSize());
	}
	
	// make very bouncy
	auto physics = ball->getComponents<BallPhysicsComponent>();
	physics[0]->setRestitution(1);
}

void Level1Scene::makeEnemy(std::shared_ptr<Entity> enemy) {
	
	// add shape component if not present
	auto checkShapes = enemy->getComponents<ShapeComponent>();
	if (checkShapes.size() == 0) {
		enemy->addComponent<ShapeComponent>();
	}
	
	// set size, origin, texture etc
	auto shape = enemy->getComponents<ShapeComponent>();
	shape[0]->setShape<sf::CircleShape>(ls::getTileSize() / 4);
	shape[0]->getShape().setFillColor({255 , 255, 255});
	shape[0]->getShape().setOrigin(Vector2f(ls::getTileSize() / 4, ls::getTileSize() / 4));
	shape[0]->setTexture(enemySprites, sf::IntRect(0,0,300,300));
	
	// add movement component if not present
	auto checkMovement = enemy->getComponents<MovementComponent>();
	if (checkMovement.size() == 0) {
		enemy->addComponent<MovementComponent>();
	}
	
	// add physics component if not present
	auto checkPhysics = enemy->getComponents<EnemyPhysicsComponent>();
	if (checkPhysics.size() == 0) {
		enemy->addComponent<EnemyPhysicsComponent>(
			Vector2f(ls::getTileSize() / 4, ls::getTileSize() / 4), 
			ls::getTileSize() / 2
		);
	}
}



/* create a beetle */

void Level1Scene::spawn() {
	
	// play beetle walking audio
	auto jukebox = makeEntity("audio");
	auto audio = jukebox->addComponent<AudioComponent>();
	audio->LoadAudio("Beetle_Walking.wav");
	audio->PlayAudio();
	
	// make beetle, put it on hole, add components and AI
	auto entity = Level1Scene::makeEntity("beetle");
	entity->setPosition(ls::getTileCentre(ls::findTiles(ls::HOLE)[0]));
	makeEnemy(entity);
	addEnemyAI(entity);
	
}



/* beetle AI methods */ 

void Level1Scene::addEnemyAI(std::shared_ptr<Entity> enemy) {
	
	// add the decision tree and state machine components
	// separated from the decision tree itself because
	// sometimes these components are already in place
	// when the tree needs updated
	
	auto decision = decisionTree();
	enemy->addComponent<DecisionTreeComponent>(decision);
	
	auto sm = enemy->addComponent<StateMachineComponent>();
	sm->addState("stationary", make_shared<StationaryState>());
	sm->addState("seek", make_shared<SeekState>(enemy, player, ls::getTileSize() / 75));
	sm->addState("flee", make_shared<FleeState>(enemy, player, ls::getTileSize() / 75));
	sm->addState("wander", make_shared<WanderState>(enemy, player, ls::getTileSize() / 75));
	
	/* 
	
	the components below are also available but haven't
	been used in this implementation
	
	*/
	
	/* // steering component
	auto move = enemy->addComponent<SteeringComponent>(player.get()); */
	
	/* // pathfinding component
	auto path = pathFind(Vector2i(1, 1), Vector2i(ls::getWidth() - 2, ls::getHeight() - 2));
	auto move = enemy->addComponent<PathfindingComponent>();
	move->setPath(path); */
	
	
}

void Level1Scene::updateEnemyAI(std::shared_ptr<Entity> enemy) {
	
	// update an existing state machine and decision tree
	// because the window has been resized
	
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
	
	// if very near ball flee from ball
	// if sort of near ball wander (to prevent juddering)
	// else if far from nome seek
	// else if mid distance from nome wander
	
	auto decision = make_shared<DistanceDecision>(
		ball,
		ls::getTileSize() * .5,
		make_shared<FleeDecision>(),
		make_shared<DistanceDecision>(
			ball,
			ls::getTileSize() * 1.5,
			make_shared<WanderDecision>(),
			make_shared<DistanceDecision>(		
				player,
				ls::getTileSize() * 2,
				make_shared<WanderDecision>(),
				make_shared<SeekDecision> ()
			)
		)
	);
	
	return decision;
}











