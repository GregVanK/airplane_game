/*
*@author: Greg VanKampen
*@file: Entity.cpp
*@description: Entity class that is to be inherited
*/
#include "Entity.h"
#include <cassert>

GEX::Entity::Entity(int points):
	_hitPoints(points)
{

}

void GEX::Entity::setVelocity(sf::Vector2f velocity)
{
	_velocity = velocity;
}

void GEX::Entity::setVelocity(float vx, float vy)
{
	_velocity.x = vx;
	_velocity.y = vy;
}

sf::Vector2f GEX::Entity::getVelocity()
{
	return _velocity;
}

void GEX::Entity::accelerate(sf::Vector2f velocity)
{
	_velocity += velocity;
}

void GEX::Entity::accelerate(float vx, float vy)
{
	_velocity.y += vy;
	_velocity.x += vx;
}

int GEX::Entity::getHitPoints() const
{
	return _hitPoints;
}

void GEX::Entity::damage(int points)
{
	assert(points > 0);
	_hitPoints -= points;
}

void GEX::Entity::repair(int points)
{
	assert(points > 0);
	_hitPoints += points;
}

void GEX::Entity::destroy()
{
	_hitPoints = 0;
}

bool GEX::Entity::isDestroyed() const
{

	return _hitPoints <= 0;
}

void GEX::Entity::remove()
{
	destroy();
}

void GEX::Entity::updateCurrent(sf::Time dt,CommandQueue& commands)
{
	move(_velocity * dt.asSeconds());
}
