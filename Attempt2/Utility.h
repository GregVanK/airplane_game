
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <cmath>
#include <assert.h>
#pragma once
namespace sf {
	class Sprite;
	class Text;
}
void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);

float			toDegrees(float radian);
float			toRadian(float degrees);
int				randomInt(int exclusiveMax);

float			length(sf::Vector2f vector);

sf::Vector2f	unitVector(sf::Vector2f vector);