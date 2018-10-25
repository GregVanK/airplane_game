#include "Pickup.h"
#include "DataTables.h"
namespace {
	const std::map<GEX::Pickup::Type, GEX::PickupData> TABLE = GEX::initalizePickupData();
}

GEX::Pickup::Pickup(Type type, const TextureManager & textures):
	Entity(1),
	_type(type),
	_sprite(textures.get(TABLE.at(type).texture), TABLE.at(type).textureRect)
{
}

unsigned int GEX::Pickup::getCategory() const
{
	return Category::Pickup;
}

sf::FloatRect GEX::Pickup::getBoundingBox() const
{
	return getWorldTransform().transformRect(_sprite.getGlobalBounds());
}

void GEX::Pickup::apply(Aircraft & player)
{
	TABLE.at(_type).action(player);
}

void GEX::Pickup::drawcurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}
