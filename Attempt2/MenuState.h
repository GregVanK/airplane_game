/*
*@author: Greg VanKampen
*@file: MenuState.h
*@description: The state of the application when the menu is active
*/
#pragma once
#include "State.h"
class MenuState : public GEX::State
{
public:
	MenuState(GEX::StateStack& stack, Context context);
	void					draw() override;
	bool					update(sf::Time dt) override;
	bool					handleEvents(const sf::Event& event) override;

	void					updateOptionText();

private:
	enum OptionNames {
		Play = 0,
		Exit
	};
	sf::Sprite _backgroundSprite;

	std::vector<sf::Text>	_options;
	std::size_t				_optionsIndex;
};

