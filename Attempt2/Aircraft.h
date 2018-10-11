/*
*@author: Greg VanKampen
*@file: Aircraft.h
*@description: Basic aircraft entity header
*/
#pragma once
#include "Entity.h"
#include "TextureManager.h"
#include "TextNode.h"
#include "Command.h"
#include "Projectile.h"
#include <SFML\Graphics\Sprite.hpp>
namespace GEX {
	
	enum class AircraftType {Eagle, Raptor,Avenger};
	class Aircraft : public Entity
	{
	public:
		Aircraft(AircraftType type,const TextureManager& textures);
		virtual void				drawcurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
		unsigned int				getCategory() const override;
		void						updateTexts(); //update mini hp/ammo
		void						fire();
		void						launchMissle();
	protected:
		void						updateCurrent(sf::Time dt, CommandQueue& commands) override;
	private:
		void						updateMovementPattern(sf::Time dt);
		float						getMaxSpeed() const;
		void						createBullets(SceneNode& node, const TextureManager& textures);
		void						createProjectile(SceneNode& node, Projectile::Type type, float xOffset, float yOffset, const TextureManager& textures);
		void						checkProjectileLauncher(sf::Time dt, CommandQueue& commands);
		bool						isAllied();
	private:
		sf::Sprite					_sprite;
		AircraftType				_type;
		TextNode*					_healthDisplay;
		TextNode*					_missileDisplay;

		float						_travelDistance;
		std::size_t					_directionIndex;

		int							_fireRateLevel;
		int							_fireSpreadLevel;

		bool						_isFiring;
		sf::Time					_fireCountdown;

		Command						_fireCommand;
	};
}

