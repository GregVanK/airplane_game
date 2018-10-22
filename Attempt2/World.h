//
//		The game world
//

#pragma once
#include<SFML/System.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>


#include "SceneNode.h"
#include "SpriteNode.h"
#include "TextureManager.h"
#include "Aircraft.h"
#include "CommandQueue.h"
#include <vector>

namespace sf {
	class RenderWindow;
}
namespace GEX {
	class World
	{
	public:
		World(sf::RenderWindow& window);
		~World();
		void							update(sf::Time dt);
		void adaptPlayerPosition();
		void adaptPlayerVelocity();
		void							draw();
		CommandQueue&					getCommandQueue();

		void							addEnemies();
		void							addEnemy(AircraftType type, float relx, float rely);
		void							spawnEnemies();

		sf::FloatRect					getViewBounds() const;
		sf::FloatRect					getBattlefieldBounds() const;
	private:
		enum Layer {
			Background = 0,
			Air,
			LayerCount
		};
		struct SpawnPoint {
			SpawnPoint(AircraftType type, float x, float y)
			:type(type),
			x(x),
			y(y){}
			AircraftType type;
			float x;
			float y;
		};
	private:
		void							loadTextures();
		void							buildScene();
		void							guideMissiles();
		void							handleCollisions();
	private:
		sf::RenderWindow&				_window;
		sf::View						_worldview;
		TextureManager					_textures;

		SceneNode						_sceneGraph;
		std::vector<SceneNode*>			_sceneLayers;
		CommandQueue					_command;
		sf::FloatRect					_worldBounds;
		sf::Vector2f					_spawnPosition;
		float							_scrollSpeeds;
		Aircraft*						_player;

		std::vector<SpawnPoint>			_enemySpawnPoints;

		std::vector<Aircraft*>			_activeEnemies;
	};


}

