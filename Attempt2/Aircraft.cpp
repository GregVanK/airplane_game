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
		_sprite(textures.get(TABLE.at(type).texture)),
		_healthDisplay(nullptr),
		_missileDisplay(nullptr),
		_travelDistance(0.f),
		_directionIndex(0),
		_fireRateLevel(1),
		_fireSpreadLevel(1),
		_isFiring(false),
		_fireCountdown(sf::Time::Zero),
		_fireCommand()
	{
		//Set up commands
		_fireCommand.category = Category::AirSceneLayer;
		_fireCommand.action = [this, &textures](SceneNode& node, sf::Time dt) {
			createBullets(node, textures);
		};

		centerOrigin(_sprite);

		std::unique_ptr<TextNode> health(new TextNode(""));
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

	void Aircraft::fire()
	{
  		if(TABLE.at(_type).fireInterval != sf::Time::Zero)
			_isFiring = true;
	}

	void Aircraft::launchMissle()
	{
	}

	void Aircraft::updateCurrent(sf::Time dt, CommandQueue& commands)
	{
		updateMovementPattern(dt);
		checkProjectileLauncher(dt, commands);
		Entity::updateCurrent(dt,commands);
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

	void Aircraft::createBullets(SceneNode & node, const TextureManager & textures)
	{
		Projectile::Type type = isAllied() ? Projectile::Type::AlliedBullet : Projectile::Type::EnemyBullet;
		switch (_fireSpreadLevel) {
		case 1:
			createProjectile(node, type, 0.f, 0.5f,textures);
			break;
		case 2:
			createProjectile(node, type, -0.5f, 0.5f, textures);
			createProjectile(node, type, 0.5f, 0.5f, textures);
			break;
		case 3:
			createProjectile(node, type, -0.75f, 0.5f, textures);
			createProjectile(node, type, 0.f, 0.5f, textures);
			createProjectile(node, type, 0.75f, 0.5f, textures);
			break;
		}
	}

	void Aircraft::createProjectile(SceneNode & node, Projectile::Type type, float xOffset, float yOffset, const TextureManager & textures)
	{
		std::unique_ptr<Projectile> projectile(new Projectile(type, textures));

		sf::Vector2f offset(xOffset * _sprite.getGlobalBounds().width, yOffset * _sprite.getGlobalBounds().height);
		sf::Vector2f velocity(0, projectile->getMaxSpeed());
		float sign = isAllied() ? -1.f : 1.f; //Set direction

		projectile->setPosition(getWorldPosition() + offset * sign);
		projectile->setVelocity(velocity * sign);
		node.attachChild(std::move(projectile));
	}

	void Aircraft::checkProjectileLauncher(sf::Time dt, CommandQueue & commands)
	{
		//enemy
		if (!isAllied())
			fire();
		//bullets
		if (_isFiring && _fireCountdown <= sf::Time::Zero) {
			commands.push(_fireCommand);
			_isFiring = false;
			_fireCountdown = TABLE.at(_type).fireInterval / (_fireRateLevel + 1.f);
		}
		else if(_fireCountdown > sf::Time::Zero)
		{
			_fireCountdown -= dt;
		}

		//if (isLaunchMissle) {
		//	commands.push(_launchMissleCommand);
		//	isLauncMissile = false;
		//}
	}

	bool Aircraft::isAllied()
	{
		return (_type == AircraftType::Eagle);
	}

}
