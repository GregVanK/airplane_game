#include "World.h"
#include"Aircraft.h"


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

		//run all commands in queue
		while (!_command.isEmpty()) {
			_sceneGraph.onCommand(_command.pop(), dt);
		}

		adaptPlayerVelocity();
		_sceneGraph.update(dt);
		adaptPlayerPosition();
		
		
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
	void World::loadTextures()
	{
		_textures.load(GEX::TextureID::Landscape, "Media/Backgrounds/Space.png");
		_textures.load(GEX::TextureID::Eagle, "Media/Textures/Eagle.png");
		_textures.load(GEX::TextureID::Raptor, "Media/Textures/Raptor.png");
		_textures.load(GEX::TextureID::Avenger, "Media/Textures/Avenger.png");
		
	}
	void World::buildScene()
	{
		//initalizes layers
		for (int i = 0; i < LayerCount; ++i) {
			SceneNode::Ptr layer(new SceneNode());
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
		//add escort planes
		std::unique_ptr<Aircraft>leftEscort(new Aircraft(AircraftType::Avenger, _textures));
		leftEscort->setPosition(-80.f, 50.f);
		_player->attachChild(std::move(leftEscort));
		std::unique_ptr<Aircraft> rightEscort(new Aircraft(AircraftType::Raptor, _textures));
		rightEscort->setPosition(80.f, 50.f);
		_player->attachChild(std::move(rightEscort)); 

		//Enemy aircrafts
		std::unique_ptr<Aircraft> enemy(new Aircraft(AircraftType::Avenger, _textures));
		enemy->setPosition(_spawnPosition.x - 100, _spawnPosition.y - 600);
		enemy->setVelocity(0.f, - _scrollSpeeds);
		enemy->setRotation(180);
		_sceneLayers[Air]->attachChild(std::move(enemy));

		enemy = std::unique_ptr<Aircraft>((new Aircraft(AircraftType::Raptor, _textures)));
		enemy->setPosition(_spawnPosition.x - 200, _spawnPosition.y - 800);
		enemy->setVelocity(50.f, -_scrollSpeeds);
		enemy->setRotation(180);
		_sceneLayers[Air]->attachChild(std::move(enemy));

		enemy = std::unique_ptr<Aircraft>((new Aircraft(AircraftType::Eagle, _textures)));
		enemy->setPosition(_spawnPosition.x - 400, _spawnPosition.y - 700);
		enemy->setVelocity(50.f, -_scrollSpeeds);
		enemy->setRotation(180);
		_sceneLayers[Air]->attachChild(std::move(enemy));
	}
}
