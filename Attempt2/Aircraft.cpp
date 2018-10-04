/*
*@author: Greg VanKampen
*@file: Aircraft.h
*@description: Basic aircraft entity
*/

#include "Aircraft.h"
#include "DataTables.h"
#include <string>
#include "Utility.h"

namespace GEX {
	
	namespace {
		const std::map<AircraftType, AircraftData> TABLE = initalizeAircraftData();
	}
	Aircraft::Aircraft(AircraftType type, const TextureManager & textures)
		:Entity(TABLE.at(type).hitpoints),
		_type(type),
		_sprite(textures.get(TABLE.at(type).texture))
	{
		sf::FloatRect bounds = _sprite.getLocalBounds();
		_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

		std::unique_ptr<TextNode> health(new TextNode("BIG PLAIN TIME!"));
		_healthDisplay = health.get();
		attachChild(std::move(health));

	}

	
	void Aircraft::drawcurrent(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(_sprite, states);
	}
	unsigned int Aircraft::getCategory() const
	{
		switch (_type) {
		case AircraftType::Eagle:
			return Category::PlayerAircraft;
			break;

		default:
			return Category::EnemyAircraft;
			break;

		}
	}

	void Aircraft::updateTexts()
	{
		_healthDisplay->setText(std::to_string(getHitPoints()) + "HP");
		_healthDisplay->setPosition(0.f, 50.f);
		_healthDisplay->setRotation(-getRotation());
	}

	void Aircraft::updateCurrent(sf::Time dt)
	{
		updateMovementPattern(dt);
		Entity::updateCurrent(dt);
		updateTexts();
	}

	void Aircraft::updateMovementPattern(sf::Time dt)
	{
		//movement pattern
		const std::vector<Direction>& directions = TABLE.at(_type).directions;
		if (!directions.empty()) {
			if (_travelDistance > (directions[_directionIndex].distance)) {
				_directionIndex = (++_directionIndex) % directions.size();
				_travelDistance = 0;
			}
			float radians = toRadian(directions[_directionIndex].angle + 90.f);
			float vx = getMaxSpeed() * std::cos(radians);
			float vy = getMaxSpeed() * std::sin(radians);
			setVelocity(vx, vy);
			_travelDistance += getMaxSpeed() * dt.asSeconds();
		}
		

		
	}

	float Aircraft::getMaxSpeed() const
	{
		return TABLE.at(_type).speed;
	}

}
