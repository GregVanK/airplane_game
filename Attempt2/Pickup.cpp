#include "Pickup.h"

sf::FloatRect GEX::Pickup::getBoundingBox() const
{
	return getWorldTransform().transformRect(_sprite.getGlobalBounds());
}
