/*
*@author: Greg VanKampen
*@file: Game.h
*@description: REPLACED WITH APPLICATION
*/
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "World.h"
#include "PlayerControl.h"
#pragma once
class Game
{
public:
	Game();
	~Game();
	void run();

private:
	void processInput();
	bool isAnyKeyPressed();
	void update(sf::Time deltaTime);
	void render();
	void updateStats(sf::Time deltaTime);
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
private:
	bool _pressUp;
	bool _pressLeft;
	bool _pressRight;
	bool _pressDown;
	bool _pressClockWise;
	bool _pressCounterClockwise;

	
	sf::Text _statText;
	sf::Time _statUpdateTime;
	unsigned int _statNumFrames;
	sf::Font _font;
	sf::RenderWindow _window;
	GEX::World _world;
	sf::Sprite _background;
	GEX::PlayerControl _player;
	sf::Vector2f _velocity;
	//sf::Texture _texture;
	//sf::Texture _bgTexture;
	static const int WIDTH = 600;
	static const int HEIGHT = 800;
	int _rotate;
	
	//to do CLEAN UP ROTATE
};

