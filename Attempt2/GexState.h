/*
*@author: Greg VanKampen
*@file: GexState.h
*@description: A secondary pause state header
*/
#pragma once
#include "State.h"
#include "TextureManager.h"
class GexState : public GEX::State
{
public:
	GexState(GEX::StateStack& stack, Context context);
	void					draw() override;
	bool					update(sf::Time dt) override;
	bool					handleEvents(const sf::Event& event) override;
private:
	sf::Sprite				_backgroundSprite;
	sf::Text				_pausedText;
	sf::Text				_gexText;
	sf::Text				_returnText;
	sf::Text				_exitText;
	GEX::TextureManager		_textures;

};

