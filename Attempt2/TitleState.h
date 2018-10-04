//@author: Greg VanKAmpen
//@description: state for displaying the title
#pragma once
#include "State.h"
class TitleState : public GEX::State
{
public:
	TitleState(GEX::StateStack& stack, Context context);
	void					draw() override;
	bool					update(sf::Time dt) override;
	bool					handleEvents(const sf::Event& event) override;
private:
	sf::Sprite				_backgroundSprite;
	sf::Text				_text;
	bool					_showText;
	sf::Time				_textEffectTime;
};

