#include "GameOverState.h"
#include "FontManager.h"
#include "Utility.h"
#include "Gamestate.h"



GameOverState::GameOverState(GEX::StateStack & stack, Context context)
	:State(stack, context),
	_gameOverText(),
	_elapsedtime(sf::Time::Zero)
{
	_gameOverText.setFont(GEX::FontManager::getInstance().getFont(GEX::FontID::Main));
	if (context.player->getMissionStatus() == GEX::MissionStatus::MissionFailure)
	_gameOverText.setString("Game Over");
	else
		_gameOverText.setString("SUCCESS!");
	_gameOverText.setCharacterSize(40);
	centerOrigin(_gameOverText);

	sf::Vector2f viewSize = context.window->getView().getSize();
	_gameOverText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);
}

void GameOverState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());
	window.draw(backgroundShape);
	window.draw(_gameOverText);
}

bool GameOverState::update(sf::Time dt)
{
	_elapsedtime += dt;
	if (_elapsedtime > sf::seconds(3)) {
		requestStackClear();
		requestStackPush(GEX::StateID::Menu);
	}
	return false;
}

bool GameOverState::handleEvents(const sf::Event & event)
{
	return false;
}
