#include "Projectile.h"
#include "DataTables.h"
#include "Utility.h"
#include "Category.h"
namespace {
	const std::map<GEX::Projectile::Type, GEX::ProjectileData>TABLE = GEX::initalizeProjectileData();
}
GEX::Projectile::Projectile(Type type, const TextureManager & textures):Entity(1),
_type(type),
_sprite(textures.get(TABLE.at(type).texture))
{
	centerOrigin(_sprite);
}

unsigned int GEX::Projectile::getCategory() const
{
	if (_type == Type::EnemyBullet)
		return Category::EnemeyProjectile;
	if (_type == Type::AlliedBullet)
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
	Entity::updateCurrent(dt, commands);
}

void GEX::Projectile::drawcurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}
