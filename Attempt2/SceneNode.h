/*
*@author: Greg VanKampen
*@file: SceneNode.h
*@description: Game object class
*/
#pragma once
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>

#include <vector>
#include <memory>
#include "Category.h"
#include "Utility.h"
#include <set>
//forward declaration

namespace GEX
{
	class CommandQueue;
	struct Command;
	class SceneNode : public sf::Transformable, public sf::Drawable
	{
	public:
		using Ptr = std::unique_ptr<SceneNode> ;
		using Pair = std::pair<SceneNode*, SceneNode*>;
	public:
		SceneNode(Category::Type category = Category::Type::None);
		virtual			~SceneNode() = default;
		SceneNode(const SceneNode&) = delete;
		SceneNode& operator=(SceneNode&) = delete;
		void			attachChild(Ptr child);
		Ptr				detachChild(const SceneNode& ptr);
		void			update(sf::Time dt, CommandQueue& commands);
		sf::Vector2f	getWorldPosition() const;
		sf::Transform	getWorldTransform() const;


		void						onCommand(const Command& command, sf::Time dt);
		virtual unsigned int		getCategory() const;
		virtual sf::FloatRect		getBoundingBox() const;
		void						drawBoundingBox(sf::RenderTarget& target, sf::RenderStates states)const;
		void			checkSceneCollision(SceneNode& rootNode, std::set<Pair>&collisionPair);
		void			checkNodeCollision(SceneNode& node, std::set<Pair>&collisionPair);
		void					removeWrecks();
		virtual bool			isDestroyed() const;
		virtual bool			isMarkedForRemoval() const;
	protected:
		virtual void	updateCurrent(sf::Time dt,CommandQueue& commands);
		void			updateChildren(sf::Time dt,CommandQueue& commands);
	private:
		void			draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		virtual void	drawcurrent(sf::RenderTarget& target, sf::RenderStates states) const;
		void			drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

		
		
		
	private:
		SceneNode*			_parent;
		std::vector <Ptr>	_children;
		Category::Type		_category;
	};
	float distance(const SceneNode& rhs, const SceneNode& lhs);
	float collision(const SceneNode& rhs, const SceneNode& lhs);
}

