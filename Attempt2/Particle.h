#pragma once
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Color.hpp>
#include <SFML\System\Time.hpp>
namespace GEX{
struct Particle {
	enum class Type {
		Propellant,
		Smoke,
		ParticleCount
	};
	sf::Vector2f position;
	sf::Color color;
	sf::Time lifetime;
};
}
