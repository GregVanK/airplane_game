#include "DataTables.h"




std::map<GEX::Pickup::Type, GEX::PickupData> GEX::initalizePickupData()
{
	std::map<GEX::Pickup::Type, GEX::PickupData> data;
	data[Pickup::Type::HealthRefill].texture = TextureID::Entities;
	data[Pickup::Type::HealthRefill].action = [](Aircraft& a) {a.repair(25); };
	data[Pickup::Type::HealthRefill].textureRect = sf::IntRect(0, 64, 40, 40);

	data[Pickup::Type::MissileRefill].texture = TextureID::Entities;
	data[Pickup::Type::MissileRefill].action = [](Aircraft& a) {a.collectMissiles(3); };
	data[Pickup::Type::MissileRefill].textureRect = sf::IntRect(40, 64, 40, 40);

	data[Pickup::Type::FireSpread].texture = TextureID::Entities;
	data[Pickup::Type::FireSpread].action = [](Aircraft& a) {a.increaseFireSpread(); };
	data[Pickup::Type::FireSpread].textureRect = sf::IntRect(80, 64, 40, 40);

	data[Pickup::Type::FireRate].texture = TextureID::Entities;
	data[Pickup::Type::FireRate].action = [](Aircraft& a) {a.increaseFireRate(); };
	data[Pickup::Type::FireRate].textureRect = sf::IntRect(120, 64, 40, 40);

	return data;
}

std::map<GEX::Projectile::Type, GEX::ProjectileData> GEX::initalizeProjectileData()
{
	std::map<Projectile::Type, ProjectileData> data;

	data[Projectile::Type::AlliedBullet].damage = 10;
	data[Projectile::Type::AlliedBullet].speed = 600.f;
	data[Projectile::Type::AlliedBullet].texture = TextureID::Entities;
	data[Projectile::Type::AlliedBullet].textureRect = sf::IntRect(175,64,3,14);

	data[Projectile::Type::EnemyBullet].damage = 10;
	data[Projectile::Type::EnemyBullet].speed = 600.f;
	data[Projectile::Type::EnemyBullet].texture = TextureID::Entities;
	data[Projectile::Type::EnemyBullet].textureRect = sf::IntRect(175, 64, 3, 14);

	data[Projectile::Type::Missile].damage = 400;
	data[Projectile::Type::Missile].speed = 400.f;
	data[Projectile::Type::Missile].texture = TextureID::Entities;
	data[Projectile::Type::Missile].textureRect = sf::IntRect(160, 64, 15, 24);

	return data;
}

std::map<GEX::Particle::Type, GEX::ParticleData> GEX::initalizeParticleData()
{
	std::map<GEX::Particle::Type, GEX::ParticleData> data;
	data[GEX::Particle::Type::Propellant].color = sf::Color(50, 150, 100);
	data[GEX::Particle::Type::Propellant].lifetime = sf::seconds(0.6f);

	data[GEX::Particle::Type::Smoke].color = sf::Color(100, 150, 50);
	data[GEX::Particle::Type::Smoke].lifetime = sf::seconds(0.8f);

	return data;
}

std::map<GEX::AircraftType, GEX::AircraftData> GEX::initalizeAircraftData()
{

	//ask for values
	std::map<GEX::AircraftType, GEX::AircraftData> data;
	data[AircraftType::Eagle].hitpoints = 100;
	data[AircraftType::Eagle].speed = 1200.f;
	data[AircraftType::Eagle].texture = TextureID::Entities;
	data[AircraftType::Eagle].textureRect = sf::IntRect(0, 0, 48, 64);
	data[AircraftType::Eagle].fireInterval = sf::seconds(0.5);
	data[AircraftType::Eagle].hasRollAnimation = true;

	data[AircraftType::Raptor].hitpoints = 20;
	data[AircraftType::Raptor].speed = 200.f;
	data[AircraftType::Raptor].texture = TextureID::Entities;
	data[AircraftType::Raptor].textureRect = sf::IntRect(144, 0, 84, 64);
	data[AircraftType::Raptor].directions.emplace_back(Direction(40.f, 100.f));
	data[AircraftType::Raptor].directions.emplace_back(Direction(-80.f, 100.f));
	data[AircraftType::Raptor].directions.emplace_back(Direction(40.f, 100.f));
	data[AircraftType::Raptor].fireInterval = sf::Time::Zero;
	data[AircraftType::Raptor].hasRollAnimation = false;


	data[AircraftType::Avenger].hitpoints = 40;
	data[AircraftType::Avenger].speed = 200.f;
	data[AircraftType::Avenger].texture = TextureID::Entities;
	data[AircraftType::Avenger].textureRect = sf::IntRect(228, 0, 60, 59);
	data[AircraftType::Avenger].directions.emplace_back(Direction(45.f, 50.f));
	data[AircraftType::Avenger].directions.emplace_back(Direction(0.f, 50.f));
	data[AircraftType::Avenger].directions.emplace_back(Direction(-45.f, 100.f));
	data[AircraftType::Avenger].directions.emplace_back(Direction(0.f, 50.f));
	data[AircraftType::Avenger].directions.emplace_back(Direction(45.f, 50.f));
	data[AircraftType::Avenger].fireInterval = sf::seconds(2);
	data[AircraftType::Avenger].hasRollAnimation = false;

	data[AircraftType::Boss].hitpoints = 1200;
	data[AircraftType::Boss].speed = 200.f;
	data[AircraftType::Boss].texture = TextureID::Boss;
	data[AircraftType::Boss].directions.push_back(Direction(0.f, 2000.f));
	data[AircraftType::Boss].directions.emplace_back(Direction(0.f, -50.f));
	data[AircraftType::Boss].directions.emplace_back(Direction(-45.f, 100.f));
	data[AircraftType::Boss].directions.emplace_back(Direction(0.f, 50.f));
	data[AircraftType::Boss].directions.emplace_back(Direction(45.f, 50.f));
	data[AircraftType::Boss].fireInterval = sf::seconds(2);
	return data;
}
