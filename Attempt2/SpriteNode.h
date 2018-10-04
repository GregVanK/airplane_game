/*
*@author: Greg VanKampen
*@file: SpriteNode.h
*@description: Scenenode for sprites
*/
#pragma once
#include "SceneNode.h"
#include <SFML/Graphics.hpp>
namespace GEX {
	class SpriteNode : public SceneNode
	{
	public:
		explicit			SpriteNode(const sf::Texture& texture);
							SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect);
							~SpriteNode();
	private:
		virtual void drawcurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	private:
		sf::Sprite _sprite;
	};
}

