/*
*@author: Greg VanKampen
*@file: PlayerControl.h
*@description: A class to handle player inputs
*/
#include "PlayerControl.h"
#include "Aircraft.h"
#include "Command.h"
#include "CommandQueue.h"
#include "Category.h"
namespace GEX {
	struct AircraftMover {
	public:
		AircraftMover(float vx, float vy) :velocity(vx, vy) {}


		void operator() (Aircraft& aircraft, sf::Time) const {
			aircraft.accelerate(velocity);
		}

		sf::Vector2f velocity;
	};
	PlayerControl::PlayerControl()
	{
		//set up bindings
		_keyBindings[sf::Keyboard::A] = Action::MoveLeft;
		_keyBindings[sf::Keyboard::W] = Action::MoveUp;
		_keyBindings[sf::Keyboard::S] = Action::MoveDown;
		_keyBindings[sf::Keyboard::D] = Action::MoveRight;
		_keyBindings[sf::Keyboard::Space] = Action::FireBullet;
		_keyBindings[sf::Keyboard::M] = Action::LaunchMissile;
		
		//connect actions to bindings
		initalizeActions();
		for (auto& pair : _actionBindings) {
			pair.second.category = Category::PlayerAircraft;
		}
		//connect rotation
		_keyBindings[sf::Keyboard::Q] = Action::RotateLeft;
		_keyBindings[sf::Keyboard::E] = Action::RotateRight;
		_actionBindings[Action::RotateLeft].action = derivedAction<Aircraft>([](Aircraft& node, sf::Time dt) {node.rotate(-1.0f); });
		_actionBindings[Action::RotateRight].action = derivedAction<Aircraft>([](Aircraft& node, sf::Time dt) {node.rotate(+1.0f); });
		_actionBindings[Action::RotateLeft].category = Category::EnemyAircraft;
		_actionBindings[Action::RotateRight].category = Category::EnemyAircraft;

		_actionBindings[Action::FireBullet].action = derivedAction<Aircraft>(std::bind(&Aircraft::fire,std::placeholders::_1));
		_actionBindings[Action::FireBullet].category = Category::PlayerAircraft;

		_actionBindings[Action::LaunchMissile].action = derivedAction<Aircraft>(std::bind(&Aircraft::launchMissle, std::placeholders::_1));
		_actionBindings[Action::LaunchMissile].category = Category::PlayerAircraft;
	}
	void PlayerControl::handleEvent(const sf::Event & event, CommandQueue & commands)
	{
		if (event.type == sf::Event::KeyPressed) {
			auto found = _keyBindings.find(event.key.code);
			if (found != _keyBindings.end()) {
				commands.push(_actionBindings[found->second]);
			}
		}
	}

	void PlayerControl::handleRealTimeInput(CommandQueue & commands)
	{
		//traverse
		for (auto pair : _keyBindings) {
			//look up action
			if (sf::Keyboard::isKeyPressed(pair.first) && isRealTimeAction(pair.second)) {
				commands.push(_actionBindings[pair.second]);
			}
		}
	}
	bool PlayerControl::isRealTimeAction(Action action) {
		switch (action) {
		case Action::MoveLeft:
		case Action::MoveRight:
		case Action::MoveUp:
		case Action::MoveDown:
		case Action::RotateLeft:
		case Action::RotateRight:
			return true;
			break;
		default:
			return false;

		}

	}
	void PlayerControl::initalizeActions() {
		const float playerSpeed = 200.f;
		_actionBindings[Action::MoveLeft].action = derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.f));
		_actionBindings[Action::MoveRight].action = derivedAction<Aircraft>(AircraftMover(+playerSpeed, 0.f));
		_actionBindings[Action::MoveUp].action = derivedAction<Aircraft>(AircraftMover(0.f, -playerSpeed));
		_actionBindings[Action::MoveDown].action = derivedAction<Aircraft>(AircraftMover(0.f, +playerSpeed));
	 }
}

