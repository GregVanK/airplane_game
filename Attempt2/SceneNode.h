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
//forward declaration

namespace GEX
{
	struct Command;
	class SceneNode : public sf::Transformable, public sf::Drawable
	{
	public:
		using Ptr = std::unique_ptr<SceneNode> ;
	public:
		SceneNode();
		virtual			~SceneNode();
		SceneNode(const SceneNode&) = delete;
		SceneNode& operator=(SceneNode&) = delete;
		void			attachChild(Ptr child);
		Ptr				detachChild(const SceneNode& ptr);
		void			update(sf::Time dt);
		sf::Vector2f	getWorldPosition() const;
		sf::Transform	getWorldTransform() const;


		void			onCommand(const Command& command, sf::Time dt);
		virtual unsigned int getCategory() const;

	protected:
		virtual void	updateCurrent(sf::Time dt);
		void			updateChildren(sf::Time dt);
	private:
		void			draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		virtual void	drawcurrent(sf::RenderTarget& target, sf::RenderStates states) const;
		void			drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;
	private:
		SceneNode* _parent;
		std::vector <Ptr> _children;
	};
}

