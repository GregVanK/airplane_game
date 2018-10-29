#include "Projectile.h"
#include "DataTables.h"
#include "Utility.h"
#include "Category.h"
#include "EmitterNode.h"
namespace {
	const std::map<GEX::Projectile::Type, GEX::ProjectileData>TABLE = GEX::initalizeProjectileData();
}
GEX::Projectile::Projectile(Type type, const TextureManager & textures):Entity(1),
_type(type),
_sprite(textures.get(TABLE.at(type).texture),TABLE.at(type).textureRect)
{
	centerOrigin(_sprite);
	if (isGuided()) {
		std::unique_ptr<EmitterNode> smoke(new EmitterNode(Particle::Type::Smoke));
		smoke->setPosition(0.f, Projectile::getBoundingBox().height / 2.f);
		attachChild(std::move(smoke));

		std::unique_ptr<EmitterNode> fire(new EmitterNode(Particle::Type::Propellant));
		fire->setPosition(0.f, Projectile::getBoundingBox().height / 2.f);
		attachChild(std::move(fire));

		
	}
	
}

unsigned int GEX::Projectile::getCategory() const
{
	if (_type == Type::EnemyBullet)
		return Category::EnemeyProjectile;
	if (_type == Type::AlliedBullet || _type == Type::Missile)
		return Category::AlliedProjectile;
	return Category::EnemeyProjectile;
}

float GEX::Projectile::getMaxSpeed() const
{
	return TABLE.at(_type).speed;
}

int GEX::Projectile::getDamage() const
{
	return TABLE.at(_type).damage;
}

void GEX::Projectile::updateCurrent(sf::Time dt, CommandQueue& commands)
{
	if (isGuided()) {
		const float APPROACH_RATE = 400.f;
		auto newVelocity = unitVector(APPROACH_RATE * dt.asSeconds()*_targetDirection + getVelocity());
		newVelocity *= getMaxSpeed();
		setVelocity(newVelocity);
		auto angle = std::atan2(newVelocity.y, newVelocity.x);
		setRotation(toDegrees(angle) + 90.f);
	}
	Entity::updateCurrent(dt, commands);
}

void GEX::Projectile::drawcurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}

sf::FloatRect GEX::Projectile::getBoundingBox() const
{
	return getWorldTransform().transformRect(_sprite.getGlobalBounds());
}

bool GEX::Projectile::isGuided() const
{
	return _type == Type::Missile;
}

void GEX::Projectile::guidedTowards(sf::Vector2f position)
{
	assert(isGuided());
	_targetDirection = unitVector(position - getWorldPosition());
}
