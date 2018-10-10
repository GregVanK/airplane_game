#pragma once
#include "Entity.h"
#include "TextureManager.h"
#include "CommandQueue.h"
namespace GEX{
	
	class Projectile : public Entity
	{
	public:
		enum class Type { AlliedBullet, EnemyBullet,Missile };
	public:
									Projectile(Type type, const TextureManager & textures);
		unsigned int				getCategory() const override;
		//sf::FloatRect				getBoundingRect() const override;
		float						getMaxSpeed() const;
		int							getDamage() const;
	private:
		void						updateCurrent(sf::Time dt,CommandQueue& commands) override;
		void						drawcurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		Type						_type;
		sf::Sprite					_sprite;
		sf::Vector2f				_targetDirection;

	};
}

