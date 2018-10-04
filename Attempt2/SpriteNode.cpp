/*
*@author: Greg VanKampen
*@file: SpriteNode.h
*@description: Scenenode for sprites
*/
#include "SpriteNode.h"


namespace GEX {



	SpriteNode::SpriteNode(const sf::Texture & texture):_sprite(texture)
	{
	}

	SpriteNode::SpriteNode(const sf::Texture & texture, const sf::IntRect & textureRect) : _sprite(texture,textureRect)
	{
	}

	SpriteNode::~SpriteNode()
	{
	}
	void SpriteNode::drawcurrent(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(_sprite, states);
	}
}
