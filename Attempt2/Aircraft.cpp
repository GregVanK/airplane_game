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
		_sprite(textures.get(TABLE.at(type).texture), TABLE.at(type).textureRect),
		explosion(textures.get(TextureID::Explosion)),
		showExplosion(true),
		_healthDisplay(nullptr),
		_missileDisplay(nullptr),
		_isMarkedForRemoval(false),
		_travelDistance(0.f),
		_directionIndex(0),
		_fireRateLevel(1),
		_fireSpreadLevel(1),
		_isFiring(false),
		_fireCountdown(sf::Time::Zero),
		_spawnPickup(false),
		_fireCommand(),
		_missileAmmo(20)
	{
		//set up explosion
		explosion.setFrameSize(sf::Vector2i(256, 256));
		explosion.setNumFrames(16);
		explosion.setDuration(sf::seconds(1));
		centerOrigin(explosion);
		//Set up commands
		_fireCommand.category = Category::AirSceneLayer;
		_fireCommand.action = [this, &textures](SceneNode& node, sf::Time dt) {
			createBullets(node, textures);
		};
		
		_launchMissileCommand.category = Category::AirSceneLayer;
		_launchMissileCommand.action = [this, &textures](SceneNode& node, sf::Time dt) {
			createProjectile(node, Projectile::Type::Missile, 0.f, 0.5f, textures);
		};
		_dropPickupCommand.category = Category::AirSceneLayer;
		_dropPickupCommand.action = [this, &textures](SceneNode& node, sf::Time dt) {
			createPickup(node, textures);
		};
		centerOrigin(_sprite);

		std::unique_ptr<TextNode> health(new TextNode(""));
		_healthDisplay = health.get();
		attachChild(std::move(health));

		std::unique_ptr<TextNode> missile(new TextNode(""));
		_missileDisplay = missile.get();
		attachChild(std::move(missile));

	}
	

	
	void Aircraft::drawcurrent(sf::RenderTarget & target, sf::RenderStates states) const
	{
		if (isDestroyed() && showExplosion) {
			target.draw(explosion,states);
		}
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

		if (isAllied())
		{
			_missileDisplay->setText("M:" + std::to_string(_missileAmmo));
			_missileDisplay->setPosition(0.f, 70.f);
		}
	}

	void Aircraft::fire()
	{
  		if(TABLE.at(_type).fireInterval != sf::Time::Zero)
			_isFiring = true;
	}

	void Aircraft::launchMissle()
	{
		_isLaunchingMissile = true;
	}

	void Aircraft::increaseFireRate()
	{
		if (_fireRateLevel < 10)
			++_fireRateLevel;
	}

	void Aircraft::increaseFireSpread()
	{
		if (_fireSpreadLevel < 3)
			++_fireSpreadLevel;
	}

	void Aircraft::collectMissiles(unsigned int count)
	{
		_missileAmmo += count;
	}

	sf::FloatRect Aircraft::getBoundingBox() const
	{
		return getWorldTransform().transformRect(_sprite.getGlobalBounds());
	}

	bool Aircraft::isMarkedForRemoval() const
	{
		return (isDestroyed() && (explosion.isFinished() || !showExplosion));
	}

	void Aircraft::updateRollAnimation()
	{
		sf::IntRect textureRect = TABLE.at(_type).textureRect;
		if (TABLE.at(_type).hasRollAnimation) {
			if (getVelocity().x < 0.f) {
				textureRect.left += textureRect.width;
			}
			else if (getVelocity().x > 0.f)
			{
				textureRect.left += 2 * textureRect.width;
			}
			_sprite.setTextureRect(textureRect);
		}
	}

	void Aircraft::updateCurrent(sf::Time dt, CommandQueue& commands)
	{
		updateRollAnimation();
		updateMovementPattern(dt);
		checkProjectileLauncher(dt, commands);
		if (isDestroyed()) {
			checkPickupDrop(commands);
			explosion.update(dt);
			return;
		}
		Entity::updateCurrent(dt,commands);
		updateTexts();
	}

	void Aircraft::checkPickupDrop(CommandQueue & commands)
	{
		if (!isAllied() && randomInt(3) == 0 && !_spawnPickup)
			commands.push(_dropPickupCommand);
		_spawnPickup = true;
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

	void Aircraft::createPickup(SceneNode & node, const TextureManager & textures)
	{
		auto type = static_cast<Pickup::Type>(randomInt(static_cast<int>(Pickup::Type::Count)));

		std::unique_ptr<Pickup> pickup(new Pickup(type, textures));
		pickup->setPosition(getWorldPosition());
		pickup->setVelocity(0.f, 0.f);
		node.attachChild(std::move(pickup));
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

		if (_isLaunchingMissile)
		{
			if (_missileAmmo > 0){
				commands.push(_launchMissileCommand);
			_isLaunchingMissile = false;
			_missileAmmo--;
			}
		}
	}

	bool Aircraft::isAllied()
	{
		return (_type == AircraftType::Eagle);
	}

	void Aircraft::remove()
	{
		Entity::remove();
		showExplosion = false;
	}

}
