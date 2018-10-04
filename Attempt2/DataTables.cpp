#include "DataTables.h"




std::map<GEX::AircraftType, GEX::AircraftData> GEX::initalizeAircraftData()
{

	//ask for values
	std::map<GEX::AircraftType, GEX::AircraftData> data;
	data[AircraftType::Eagle].hitpoints = 100;
	data[AircraftType::Eagle].speed = 200.f;
	data[AircraftType::Eagle].texture = TextureID::Eagle;


	data[AircraftType::Raptor].hitpoints = 20;
	data[AircraftType::Raptor].speed = 160.f;
	data[AircraftType::Raptor].texture = TextureID::Raptor;
	data[AircraftType::Raptor].directions.emplace_back(Direction(45.f, 80.f));
	data[AircraftType::Raptor].directions.emplace_back(Direction(-45.f, 160.f));
	data[AircraftType::Raptor].directions.emplace_back(Direction(45.f, 80.f));


	data[AircraftType::Avenger].hitpoints = 40;
	data[AircraftType::Avenger].speed = 100.f;
	data[AircraftType::Avenger].texture = TextureID::Avenger;
	data[AircraftType::Avenger].directions.emplace_back(Direction(45.f, 50.f));
	data[AircraftType::Avenger].directions.emplace_back(Direction(0.f, 50.f));
	data[AircraftType::Avenger].directions.emplace_back(Direction(-45.f, 100.f));
	data[AircraftType::Avenger].directions.emplace_back(Direction(0.f, 50.f));
	data[AircraftType::Avenger].directions.emplace_back(Direction(45.f, 50.f));
	return data;
}
