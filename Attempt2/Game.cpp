/*
*@author: Greg VanKampen
*@file: Game.cpp
*@description: REPLACED WITH APPLICATION
*/
#include "Game.h"
#include <string>

namespace {
	const sf::IntRect _spriteLeft(48, 0, 48, 64);
	const sf::IntRect _spriteRight(96, 0, 48, 64);
	const sf::IntRect _spriteNeutral(0, 0, 48, 64);


}

Game::Game()
	: _window(sf::VideoMode(HEIGHT, WIDTH), "Buster Blaster"),
	_world(_window),
	_statText(),
	_statUpdateTime(sf::Time::Zero),
	_statNumFrames(0),
	_pressUp(false),
	_pressDown(false),
	_pressLeft(false),
	_pressRight(false)
	
{

	if (_font.loadFromFile("Media/Sansation.ttf")) {
		//error
	}
	_statText.setFont(_font);
	_statText.setPosition(5.0f, 5.0f);
	_statText.setCharacterSize(20);
	_statText.setString("FPS:\nUpdateTime:\nX:Y:R:");
}


Game::~Game()
{
}

void Game::run() {
	const sf::Time SPF = sf::seconds(1.0f / 60.0f);
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (_window.isOpen())
	{
		//sf::Time deltaTime = clock.restart();
		processInput();
		timeSinceLastUpdate = clock.restart();
		while (timeSinceLastUpdate > SPF)
		{
			update(SPF);
			updateStats(SPF);
			timeSinceLastUpdate -= SPF;
		}
		update(timeSinceLastUpdate);
		updateStats(timeSinceLastUpdate);
		render();
	}
}

void Game::processInput() {
	GEX::CommandQueue& commands = _world.getCommandQueue();
	sf::Event event;
	while (_window.pollEvent(event))
	{
		_player.handleEvent(event, commands);
		if(event.type == sf::Event::Closed)
		{
			_window.close();
		}
	}
	_player.handleRealTimeInput(commands);
}

bool Game::isAnyKeyPressed()
{
	for (int k = -1; k < sf::Keyboard::KeyCount; ++k)
	{
		if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(k)))
			return true;
	}
	return false;
}

void Game::update(sf::Time deltaTime)
{
	_world.update(deltaTime);
}

void Game::render()
{
	_window.clear();
	_world.draw();
	_window.setView(_window.getDefaultView());
	_window.draw(_statText);
	_window.display();
	
}


void Game::updateStats(sf::Time deltaTime)
{
	_statUpdateTime += deltaTime;
	_statNumFrames += 1;
	if (_statUpdateTime > sf::seconds(1))
	{
		_statText.setString("FPS: " + std::to_string(_statNumFrames) + "\nUpdate Time: "+ std::to_string(_statUpdateTime.asMicroseconds() /_statNumFrames)+ "\nX: " + std::to_string(_velocity.x) + " Y: " + std::to_string(_velocity.y) + " R: " + std::to_string(_rotate) );

		_statNumFrames = 0;
		_statUpdateTime -= sf::seconds(1);
	}
	

}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
}
