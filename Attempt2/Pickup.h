/*
Author: Greg V
*/
#include"Entity.h"
#include "TextureManager.h"
#pragma once
namespace GEX {
	class Pickup : public Entity
	{
		
	public:
		enum class Type {
			HealthRefill,
			MissileRefill,
			FireSpread,
			FireRate
		};
		Pickup(Type type, const TextureManager& textures);
		~Pickup() = default;

		unsigned int			getCategory() const override;
		sf::FloatRect			getBoundingBox()const override;
		sf::Sprite				_sprite;
	};
}

