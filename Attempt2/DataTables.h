#pragma once
#include "TextureManager.h"
#include "Aircraft.h"
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
	};
	std::map<AircraftType, AircraftData> initalizeAircraftData();
}
