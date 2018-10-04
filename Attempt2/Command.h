/*
*@author: Greg VanKampen
*@file: Command.h
*@description: Commands objects that are loaded into a queue
*/
#pragma once
#include "SFML\System\Time.hpp"
#include<functional>
#include <assert.h>
namespace GEX {

	//forward declarion
	class SceneNode;
	struct Command
	{
	public:
		Command();
		std::function<void(SceneNode&, sf::Time)>		action;
		unsigned int									category;

	};
	template <typename GameObject, typename Function>
	std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn) {
		return [=](SceneNode& node, sf::Time dt) {
			assert(dynamic_cast<GameObject*>(&node) != nullptr);
			fn(static_cast<GameObject&>(node), dt);
		};
	}
}

