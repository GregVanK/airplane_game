/*
Author: Greg V
*/
#include"Entity.h"
#include "TextureManager.h"
#include "Aircraft.h"
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
		void					apply(Aircraft& player);
		
	private:
		void					drawcurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		sf::Sprite				_sprite;
		Type					_type;
	};
}

