/*
*@author: Greg VanKampen
*@file: SceneNode.cpp
*@description: Game object class
*/
#include "SceneNode.h"
#include <algorithm>
#include <cassert>
#include "Command.h"
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\RenderTarget.hpp>
namespace GEX {
	SceneNode::SceneNode(Category::Type category) :
		_children(),
		_parent(nullptr),
		_category(category)
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
	void SceneNode::update(sf::Time dt, CommandQueue& commands)
	{
		updateCurrent(dt,commands);
		updateChildren(dt,commands);
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
		return _category;
	}
	sf::FloatRect SceneNode::getBoundingBox() const
	{
		return sf::FloatRect();
	}
	void SceneNode::drawBoundingBox(sf::RenderTarget & target, sf::RenderStates states) const
	{
		sf::FloatRect rect = getBoundingBox();

		sf::RectangleShape box;
		box.setPosition(sf::Vector2f(rect.left, rect.top));
		box.setSize(sf::Vector2f(rect.width, rect.height));
		box.setFillColor(sf::Color::Transparent);
		box.setOutlineColor(sf::Color::Green);
		box.setOutlineThickness(5.f);
		target.draw(box);
	}
	sf::Vector2f SceneNode::getWorldPosition() const
	{
		return getWorldTransform() * sf::Vector2f();
	}
	
	void SceneNode::updateCurrent(sf::Time dt, CommandQueue& commands)
	{
		//do nothing
	}
	void SceneNode::updateChildren(sf::Time dt, CommandQueue& commands)
	{
		for (Ptr& child : _children) {
			child->update(dt,commands);
		}
	}
	void SceneNode::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		drawcurrent(target, states);
		drawChildren(target, states);

		drawBoundingBox(target, states);
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
	void SceneNode::checkSceneCollision(SceneNode & rootNode, std::set<Pair>& collisionPair)
	{
		checkNodeCollision(rootNode, collisionPair);
		for (Ptr& c : rootNode._children)
			checkSceneCollision(*c, collisionPair);
	}
	void SceneNode::checkNodeCollision(SceneNode & node, std::set<Pair>& collisionPair)
	{
		if (this != &node && collision(*this, node) && !isDestroyed() && !node.isDestroyed())
			collisionPair.insert(std::minmax(this, &node));

		for (Ptr& c : _children)
			c->checkNodeCollision(node, collisionPair);
	}
	bool SceneNode::isDestroyed() const
	{
		return false;
	}
	float distance(const SceneNode & rhs, const SceneNode & lhs)
	{
		return length(lhs.getWorldPosition() - rhs.getWorldPosition());
	}
	float collision(const SceneNode & rhs, const SceneNode & lhs)
	{
		return lhs.getBoundingBox().intersects(rhs.getBoundingBox());
	}
}
