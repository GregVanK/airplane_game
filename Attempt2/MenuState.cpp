/*
*@author: Greg VanKampen
*@file: MenuState.cpp
*@description: The state of the application when the menu is active
*/

#include "MenuState.h"
#include "Utility.h"
#include "FontManager.h"
MenuState::MenuState(GEX::StateStack & stack, Context context)
	:State(stack,context),_options(),_optionsIndex(0)
{
	sf::Texture& texture = context.textures->get(GEX::TextureID::TitleScreen);
	_backgroundSprite.setTexture(texture);

	//set up menu
	sf::Text playOption;
	playOption.setFont(GEX::FontManager::getInstance().getFont(GEX::FontID::Main));
	playOption.setString("Play");
	centerOrigin(playOption);
	playOption.setPosition(context.window->getView().getSize() / 2.f);
	_options.push_back(playOption);
	//exit
	sf::Text exitOption;
	exitOption.setFont(GEX::FontManager::getInstance().getFont(GEX::FontID::Main));
	exitOption.setString("Exit");
	centerOrigin(exitOption);
	exitOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f,30.f));
	_options.push_back(exitOption);

	updateOptionText();
}

void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());
	window.draw(_backgroundSprite);
	for (const sf::Text& text : _options)
		window.draw(text);
}

bool MenuState::update(sf::Time dt)
{
	return true;
}

bool MenuState::handleEvents(const sf::Event & event)
{
	if(event.type != sf::Event::KeyPressed)
		return true;

	if (event.key.code == sf::Keyboard::Return)
	{
		if (_optionsIndex == Play)
		{
			requestStackPop();
			requestStackPush(GEX::StateID::Game);
		}
		else if (_optionsIndex == Exit)
		{
			requestStackPop();
		}
	}
	else if (event.key.code == sf::Keyboard::W) {
		if (_optionsIndex > 0)
			_optionsIndex--;
		else
			_optionsIndex = _options.size()-1;
	}
	else if (event.key.code == sf::Keyboard::S) {
		if (_optionsIndex < _options.size() - 1)
			_optionsIndex++;
		else
			_optionsIndex = 0;
	}
	updateOptionText();
	return true;
}

void MenuState::updateOptionText()
{
	if (_options.empty())
		return;
	for (sf::Text& text : _options) {
		text.setFillColor(sf::Color::White);
		text.setOutlineColor(sf::Color::Black);
	}
	_options[_optionsIndex].setFillColor(sf::Color::Red);
}
