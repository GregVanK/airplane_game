#include "Utility.h"
#define _USE_MATH_DEFINES
#ifndef  M_PI
#define M_PI (3.141592)
#endif // ! M_PI

void centerOrigin(sf::Sprite & sprite)
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width/2.f, bounds.height/2.f);
}

void centerOrigin(sf::Text & text)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(bounds.width/2.f, bounds.height/2.f);
}

float toDegrees(float radian)
{
	return 180.f / static_cast<float>(M_PI) * radian;
}

//
float toRadian(float degrees)
{
	return static_cast<float>(M_PI)/ 180 * degrees;
}

int randomInt(int exclusiveMax)
{
	return 0;
}

float length(sf::Vector2f vector)
{
	return std::sqrt(vector.x*vector.x + vector.y * vector.y);
}

sf::Vector2f unitVector(sf::Vector2f vector)
{

	assert(vector != sf::Vector2f(0.f, 0.f));
	return vector / length(vector);
}
