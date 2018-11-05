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
#include "PostEffect.h"
#include "BloomEffect.h"

namespace sf {
	class RenderTarget;
}
namespace GEX {
	class World
	{
	public:
		World(sf::RenderTarget& outputTarget);
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
		bool							hasAlivePlayer() const;
		bool							hasPlayerReachedEnd() const;
		void							destroyEntitesOutOfView();
	private:
		enum Layer {
			Background = 0,
			LowerAir,
			UpperAir,
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
		BloomEffect						_bloomEffect;
		sf::RenderTarget&				_target;
		sf::RenderTexture				_sceneTexture;
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

