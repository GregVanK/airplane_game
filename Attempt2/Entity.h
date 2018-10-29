/*
*@author: Greg VanKampen
*@file: Entity.h
*@description: Entity class that is to be inherited
*/
#pragma once
#include "SceneNode.h"
namespace GEX {

	class Entity : public SceneNode
	{
	public:
		explicit		Entity(int points);
		void			setVelocity(sf::Vector2f velocity);
		void			setVelocity(float vx, float vy);
		sf::Vector2f	getVelocity();
		void 			accelerate(sf::Vector2f velocity);
		void			accelerate(float vx, float vy);
		int				getHitPoints() const;
		void			damage(int points);
		void			repair(int points);
		void			destroy();
		bool			isDestroyed() const override;
		virtual void			remove();
	protected:
		void	updateCurrent(sf::Time dt,CommandQueue& commands) override;
	private:
		sf::Vector2f	_velocity;
		int				_hitPoints;
		
	};
}

