/*
*@author: Greg VanKampen
*@file: SceneNode.cpp
*@description: Game object class
*/
#include "SceneNode.h"
#include <algorithm>
#include <cassert>
#include "Command.h"
namespace GEX {
	SceneNode::SceneNode() :
		_children(),
		_parent(nullptr)
	{

	}
	SceneNode::~SceneNode()
	{
	}

	void SceneNode::attachChild(Ptr child) {
		child->_parent = this;
		_children.push_back(std::move(child));
	}
	SceneNode::Ptr SceneNode::detachChild(const SceneNode & node)
	{
		auto found = std::find_if(_children.begin(), _children.end(), [&](Ptr& p) {
			return &node == p.get();
		});
		assert(found != _children.end());
		Ptr result = std::move(*found);
		_children.erase(found);
		return result;

	}
	void SceneNode::update(sf::Time dt)
	{
		updateCurrent(dt);
		updateChildren(dt);
	}
	sf::Transform SceneNode::getWorldTransform() const
	{
		sf::Transform transform = sf::Transform::Identity;
		for (const SceneNode* node = this; node != nullptr; node = node->_parent)
			transform = node->getTransform() * transform;
		return transform;
	}

	void SceneNode::onCommand(const Command & command, sf::Time dt)
	{
		if (command.category & getCategory())
			command.action(*this, dt);
		for (Ptr& child : _children)
			child->onCommand(command, dt);
	}

	unsigned int SceneNode::getCategory() const
	{
		return Category::Type::None;
	}
	sf::Vector2f SceneNode::getWorldPosition() const
	{
		return getWorldTransform() * sf::Vector2f();
	}
	
	void SceneNode::updateCurrent(sf::Time dt)
	{
		//do nothing
	}
	void SceneNode::updateChildren(sf::Time dt)
	{
		for (Ptr& child : _children) {
			child->update(dt);
		}
	}
	void SceneNode::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		drawcurrent(target, states);
		drawChildren(target, states);
	}
	void SceneNode::drawcurrent(sf::RenderTarget & target, sf::RenderStates states) const
	{
		//default : nothing
	}
	void SceneNode::drawChildren(sf::RenderTarget & target, sf::RenderStates states) const
	{
		 //CHECK
		for (const Ptr& child : _children) {
			child->draw(target, states);
		}
	}
}
