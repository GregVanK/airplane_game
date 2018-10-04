/*
*@author: Greg VanKampen
*@file: PauseState.h
*@description: The state of the application when the pause menu is active
*/
#pragma once
#include "State.h"
class PauseState : public GEX::State
{
public:
	PauseState(GEX::StateStack& stack, Context context);
	void					draw() override;
	bool					update(sf::Time dt) override;
	bool					handleEvents(const sf::Event& event) override;

private:
	sf::Sprite				_backgroundSprite;
	sf::Text				_pausedText;
	sf::Text				_instructionText;
};

