#include "Utility.h"
#define _USE_MATH_DEFINES
#ifndef  M_PI
#define M_PI (3.141592)
#endif // ! M_PI
#include <random>

namespace {
	std::default_random_engine createRandomEngine() {
		auto seed = static_cast<unsigned long>(std::time(nullptr));
		return std::default_random_engine(seed);
	}
	auto RandomEngine = createRandomEngine();
}

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

void centerOrigin(GEX::Animation & animation)
{
	sf::FloatRect bounds = animation.getLocalBounds();
	animation.setOrigin(std::floor(bounds.width / 2.f), std::floor(bounds.height / 2.f));
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
	std::uniform_int_distribution<> distr(0, exclusiveMax - 1);
	return distr(RandomEngine);
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
