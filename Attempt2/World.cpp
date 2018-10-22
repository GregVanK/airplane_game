#include "World.h"
#include"Aircraft.h"
#include "Pickup.h"


namespace GEX {

	World::World(sf::RenderWindow& window) : _window(window),
		_worldview(window.getDefaultView()),
		_textures(),
		_sceneGraph(),
		_sceneLayers(),
		_worldBounds(0.f, 0.f, _worldview.getSize().x, 5000.f),
		_spawnPosition(_worldview.getSize().x / 2.f, _worldBounds.height - _worldview.getSize().y / 2.f),
		_scrollSpeeds(-50.f)
	{
		loadTextures();
		buildScene();

		//prep the view
		_worldview.setCenter(_spawnPosition);
	}


	World::~World()
	{
	}
	void World::update(sf::Time dt)
	{
		//scroll
		_worldview.move(0, _scrollSpeeds * dt.asSeconds());
		_player->setVelocity(0.f, 0.f);

		guideMissiles();

		//run all commands in queue
		while (!_command.isEmpty()) {
			_sceneGraph.onCommand(_command.pop(), dt);
		}

		handleCollisions();

		adaptPlayerVelocity();
		_sceneGraph.update(dt,_command);
		adaptPlayerPosition();
		spawnEnemies();
		
		
	}
	void World::adaptPlayerPosition() {
		const float BORDER_DISTANCE = 40.f;
		sf::FloatRect viewBounds(_worldview.getCenter() - _worldview.getSize() / 2.f, _worldview.getSize()); //ASK
		sf::Vector2f position = _player->getPosition();
		position.x = std::max(position.x, viewBounds.left + BORDER_DISTANCE);
		position.x = std::min(position.x, viewBounds.left + viewBounds.width - BORDER_DISTANCE);
		position.y = std::max(position.y, viewBounds.top + BORDER_DISTANCE);
		position.y = std::min(position.y, viewBounds.top + viewBounds.height - BORDER_DISTANCE);

		_player->setPosition(position);
	}
	void World::adaptPlayerVelocity() {
		sf::Vector2f velocity = _player->getVelocity();
		if (velocity.x != 0.f && velocity.y != 0.f)
			_player->setVelocity(velocity / std::sqrt(2.f));
	}
	void World::draw()
	{
		_window.setView(_worldview);
		_window.draw(_sceneGraph);
	}
	CommandQueue & World::getCommandQueue()
	{
		return _command;
	}
	void World::addEnemies()
	{
		addEnemy(AircraftType::Raptor, -250.f, 800.f);
		addEnemy(AircraftType::Raptor, -500.f, 900.f);
		addEnemy(AircraftType::Raptor, 500.f, 900.f);
		addEnemy(AircraftType::Raptor, 250.f, 1500.f);
		addEnemy(AircraftType::Raptor, 350.f, 1500.f);
		addEnemy(AircraftType::Raptor, 250.f, 1500.f);
		addEnemy(AircraftType::Raptor, 150.f, 1500.f);
		addEnemy(AircraftType::Raptor, -50.f, 1500.f);
		addEnemy(AircraftType::Raptor, 150.f, 1500.f);
		addEnemy(AircraftType::Raptor, 250.f, 1500.f);
		addEnemy(AircraftType::Raptor, 350.f, 1500.f);

		addEnemy(AircraftType::Avenger, -70.f, 900.f);
		addEnemy(AircraftType::Avenger, -200.f, 700.f);
		addEnemy(AircraftType::Avenger, -150.f, 300.f);
		addEnemy(AircraftType::Avenger, 70.f, 500.f);
		addEnemy(AircraftType::Avenger, 120.f, 1200.f);

		std::sort(_enemySpawnPoints.begin(), _enemySpawnPoints.end(), [](SpawnPoint lhs, SpawnPoint rhs) {
			return lhs.y < rhs.y;
		});

	}
	void World::addEnemy(AircraftType type, float relx, float rely)
	{
		SpawnPoint spawnPoint(type, _spawnPosition.x + relx, _spawnPosition.y - rely);
		_enemySpawnPoints.push_back(spawnPoint);
	}
	void World::spawnEnemies()
	{
		while (!_enemySpawnPoints.empty() &&
			_enemySpawnPoints.back().y > getBattlefieldBounds().top) 
		{
			auto spawnPoint = _enemySpawnPoints.back();
			std::unique_ptr<Aircraft> enemy(new Aircraft(spawnPoint.type, _textures));
			enemy->setPosition(spawnPoint.x, spawnPoint.y);
			enemy->setRotation(180);
			_sceneLayers[Air]->attachChild(std::move(enemy));
			_enemySpawnPoints.pop_back();
		}
	}
	sf::FloatRect World::getViewBounds() const
	{
		return sf::FloatRect(_worldview.getCenter() - _worldview.getSize() / 2.f, _worldview.getSize());
	}
	sf::FloatRect World::getBattlefieldBounds() const
	{
		sf::FloatRect bounds = getViewBounds();
		bounds.top -= 100.f;
		bounds.height += 100.f;
		return bounds;
	}
	void World::loadTextures()
	{
		_textures.load(GEX::TextureID::Landscape, "Media/Backgrounds/Space.png");
		_textures.load(GEX::TextureID::Eagle, "Media/Textures/Eagle.png");
		_textures.load(GEX::TextureID::Raptor, "Media/Textures/Raptor.png");
		_textures.load(GEX::TextureID::Avenger, "Media/Textures/Avenger.png");
		_textures.load(GEX::TextureID::Bullet, "Media/Textures/Bullet.png");
		_textures.load(GEX::TextureID::Missile, "Media/Textures/Missile.png");
		_textures.load(GEX::TextureID::HealthRefill, "Media/Textures/HealthRefill.png");
		_textures.load(GEX::TextureID::FireRate, "Media/Textures/FireRate.png");
		_textures.load(GEX::TextureID::FireSpread, "Media/Textures/FireSpread.png");
		_textures.load(GEX::TextureID::MissileRefill, "Media/Textures/MissileRefill.png");
		
	}
	void World::buildScene()
	{
		//initalizes layers
		for (int i = 0; i < LayerCount; ++i) {
			auto category = (i == Air) ? Category::Type::AirSceneLayer : Category::Type::None;
			SceneNode::Ptr layer(new SceneNode(category));
			_sceneLayers.push_back(layer.get());
			_sceneGraph.attachChild(std::move(layer));
		}
		//draw background
		sf::Texture& texture = _textures.get(TextureID::Landscape);
		sf::IntRect textureRect(_worldBounds);
		texture.setRepeated(true);
		std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
		backgroundSprite->setPosition(_worldBounds.left, _worldBounds.top);
		_sceneLayers[Background]->attachChild(std::move(backgroundSprite));

		//add player aircraft & game objects
		std::unique_ptr<Aircraft> leader(new Aircraft(AircraftType::Eagle, _textures));
		leader->setPosition(_spawnPosition);
		leader->setVelocity(50.f, _scrollSpeeds);
		_player = leader.get();
		_sceneLayers[Air]->attachChild(std::move(leader));
		//add escort planes;

		//Enemy aircrafts
		addEnemies();
	}
	void World::guideMissiles()
	{
		//build a list of active Enemies
		Command enemyCollector;
		enemyCollector.category = Category::EnemyAircraft;
		enemyCollector.action = derivedAction<Aircraft>([this](Aircraft&  enemy, sf::Time dt) {
			if (!enemy.isDestroyed())
				_activeEnemies.push_back(&enemy);
		});

		Command missileGuider;
		missileGuider.category = Category::AlliedProjectile;
		missileGuider.action = derivedAction<Projectile>([this](Projectile& missile, sf::Time dt) {
			if (!missile.isGuided())
				return;
			float minDistance = std::numeric_limits<float>::max();
			Aircraft* closestEnemy = nullptr;
			for (Aircraft* e : _activeEnemies) {
				auto d = distance(missile, *e);
				if (d < minDistance) {
					minDistance = d;
					closestEnemy = e;
				}

			}
			if (closestEnemy) {
				missile.guidedTowards(closestEnemy->getWorldPosition());
			}

		});
		_command.push(enemyCollector);
		_command.push(missileGuider);
		_activeEnemies.clear();

	}
	bool matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2)
	{
		unsigned int category1 = colliders.first->getCategory();
		unsigned int category2 = colliders.second->getCategory();

		if (type1 & category1  && type2 & category2) {
			return true;
		}
		if (type1 & category2  && type2 & category1) {
			std::swap(colliders.first, colliders.second);
			return true;
		}
		return false;
	}

	void World::handleCollisions()
	{
		//build list of colliding pairs of scenenodes
		std::set<SceneNode::Pair> collisionPairs;
		_sceneGraph.checkSceneCollision(_sceneGraph, collisionPairs);
		for (SceneNode::Pair pair : collisionPairs) {
			if (matchesCategories(pair, Category::Type::PlayerAircraft, Category::Type::EnemyAircraft)) {
				auto& player = static_cast<Aircraft&>(*(pair.first));
				auto& enemy = static_cast<Aircraft&>(*(pair.second));
				player.damage(enemy.getHitPoints());
				enemy.destroy();
			}
			else if (matchesCategories(pair, Category::Type::PlayerAircraft, Category::Type::Pickup)) {
				auto& player = static_cast<Aircraft&>(*(pair.first));
				auto& pickup = static_cast<Pickup&>(*(pair.second));
				pickup.apply(player);
				pickup.destroy();
			}
			else if (matchesCategories(pair, Category::Type::PlayerAircraft, Category::Type::EnemeyProjectile) ||
				(matchesCategories(pair, Category::Type::EnemyAircraft, Category::Type::AlliedProjectile))) {
				auto& aircraft = static_cast<Aircraft&>(*(pair.first));
				auto& projectile = static_cast<Projectile&>(*(pair.second));
				
 				aircraft.damage(projectile.getDamage());
				projectile.destroy();

			}
		}
	}
}
