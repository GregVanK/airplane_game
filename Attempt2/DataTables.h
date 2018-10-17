#pragma once
#include "TextureManager.h"
#include "Aircraft.h"
#include "Projectile.h"
#include "Pickup.h"
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
		std::vector<Direction>	directions;
		sf::Time				fireInterval;
	};

	struct ProjectileData {
		int						damage;
		float					speed;
		TextureID				texture;
	};
	struct PickupData {
		std::function<void(Aircraft&)>	action;
		TextureID						texture;
	};
	std::map<Pickup::Type, PickupData>		initalizePickupData();
	std::map<Projectile::Type, ProjectileData> initalizeProjectileData();
	std::map<AircraftType, AircraftData> initalizeAircraftData();
}
