#pragma once
#include "TextureManager.h"
#include "Aircraft.h"
#include "Projectile.h"
#include "Pickup.h"
#include "Particle.h"
#include <map>
namespace GEX {
	struct Direction {
		Direction(float a, float b)
			:angle(a),
			distance(b) 
		{}

		float					angle;
		float					distance;
	};
	struct AircraftData {
		int						hitpoints;
		float					speed;
		TextureID				texture;
		sf::IntRect				textureRect;
		std::vector<Direction>	directions;
		sf::Time				fireInterval;
		bool					hasRollAnimation;
	};

	struct ProjectileData {
		int						damage;
		float					speed;
		TextureID				texture;
		sf::IntRect				textureRect;
	};
	struct PickupData {
		std::function<void(Aircraft&)>	action;
		TextureID						texture;
		sf::IntRect						textureRect;
	};

	struct ParticleData {
		sf::Color		color;
		sf::Time		lifetime;
	};
	std::map<Pickup::Type, PickupData>		initalizePickupData();
	std::map<Projectile::Type, ProjectileData> initalizeProjectileData();
	
	std::map<Particle::Type, ParticleData> initalizeParticleData();
	std::map<AircraftType, AircraftData> initalizeAircraftData();
}
