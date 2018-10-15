#include "DataTables.h"





std::map<GEX::Projectile::Type, GEX::ProjectileData> GEX::initalizeProjectileData()
{
	std::map<Projectile::Type, ProjectileData> data;

	data[Projectile::Type::AlliedBullet].damage = 10;
	data[Projectile::Type::AlliedBullet].speed = 600.f;
	data[Projectile::Type::AlliedBullet].texture = TextureID::Bullet;

	data[Projectile::Type::EnemyBullet].damage = 10;
	data[Projectile::Type::EnemyBullet].speed = 600.f;
	data[Projectile::Type::EnemyBullet].texture = TextureID::Bullet;

	data[Projectile::Type::Missile].damage = 400;
	data[Projectile::Type::Missile].speed = 150.f;
	data[Projectile::Type::Missile].texture = TextureID::Missile;

	return data;
}

std::map<GEX::AircraftType, GEX::AircraftData> GEX::initalizeAircraftData()
{

	//ask for values
	std::map<GEX::AircraftType, GEX::AircraftData> data;
	data[AircraftType::Eagle].hitpoints = 100;
	data[AircraftType::Eagle].speed = 1200.f;
	data[AircraftType::Eagle].texture = TextureID::Eagle;
	data[AircraftType::Eagle].fireInterval = sf::seconds(1);

	data[AircraftType::Raptor].hitpoints = 20;
	data[AircraftType::Raptor].speed = 200.f;
	data[AircraftType::Raptor].texture = TextureID::Raptor;
	data[AircraftType::Raptor].directions.emplace_back(Direction(20.f, 100.f));
	data[AircraftType::Raptor].directions.emplace_back(Direction(-40.f, 400.f));
	data[AircraftType::Raptor].directions.emplace_back(Direction(20.f, 100.f));
	data[AircraftType::Raptor].fireInterval = sf::Time::Zero;


	data[AircraftType::Avenger].hitpoints = 40;
	data[AircraftType::Avenger].speed = 200.f;
	data[AircraftType::Avenger].texture = TextureID::Avenger;
	data[AircraftType::Avenger].directions.emplace_back(Direction(45.f, 50.f));
	data[AircraftType::Avenger].directions.emplace_back(Direction(0.f, 50.f));
	data[AircraftType::Avenger].directions.emplace_back(Direction(-45.f, 100.f));
	data[AircraftType::Avenger].directions.emplace_back(Direction(0.f, 50.f));
	data[AircraftType::Avenger].directions.emplace_back(Direction(45.f, 50.f));
	data[AircraftType::Avenger].fireInterval = sf::seconds(2);

	return data;
}
