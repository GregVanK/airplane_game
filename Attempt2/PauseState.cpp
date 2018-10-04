/*
*@author: Greg VanKampen
*@file: PauseState.cpp
*@description: The state of the application when the pause menu is active
*/
#include "PauseState.h"
#include "Utility.h"
#include "FontManager.h"

PauseState::PauseState(GEX::StateStack & stack, Context context)
	:State(stack,context),
	_backgroundSprite(),
	_pausedText(),
	_instructionText()
{
	_pausedText.setFont(GEX::FontManager::getInstance().getFont(GEX::FontID::Main));
	_pausedText.setString("Game Paused");
	_pausedText.setCharacterSize(40);
	centerOrigin(_pausedText);
	

	_instructionText.setFont(GEX::FontManager::getInstance().getFont(GEX::FontID::Main));
	_instructionText.setString("(Press Backspace to return to the main menu");
	_instructionText.setCharacterSize(40);
	centerOrigin(_instructionText);
	sf::Vector2f viewSize = context.window->getView().getSize();
	_pausedText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);
	_instructionText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);

}

void PauseState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());
	window.draw(backgroundShape);
	window.draw(_pausedText);
	window.draw(_instructionText);

}

bool PauseState::update(sf::Time dt)
{
	return false;
}

bool PauseState::handleEvents(const sf::Event & event)
{
	if (event.type != sf::Event::KeyPressed)
		return false;

	if (event.key.code == sf::Keyboard::Escape)
		requestStackPop();
	if (event.key.code == sf::Keyboard::BackSpace)
	{
		requestStackClear();
		requestStackPush(GEX::StateID::Menu);
	}
	return false;
}
