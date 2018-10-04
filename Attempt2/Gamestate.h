/*
*@author: Greg VanKampen
*@file: GameState.h
*@description: The state of the application when the game is running
*/
#pragma once
#include "State.h"
#include "World.h"
#include "PlayerControl.h"

class Gamestate : public GEX::State
{
public:
	Gamestate(GEX::StateStack& stack, Context context);
	void draw() override;
	bool update(sf::Time dt) override;
	bool handleEvents(const sf::Event& event) override;
private:
	GEX::World _world;
	GEX::PlayerControl& player;

};

