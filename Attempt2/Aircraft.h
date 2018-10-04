/*
*@author: Greg VanKampen
*@file: Aircraft.h
*@description: Basic aircraft entity header
*/
#pragma once
#include "Entity.h"
#include "TextureManager.h"
#include "TextNode.h"
#include <SFML\Graphics\Sprite.hpp>
namespace GEX {
	
	enum class AircraftType {Eagle, Raptor,Avenger};
	class Aircraft : public Entity
	{
	public:
		Aircraft(AircraftType type,const TextureManager& textures);
		virtual void				drawcurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
		unsigned int				getCategory() const override;
		void						updateTexts(); //update mini hp/ammo
	protected:
		void						updateCurrent(sf::Time dt) override;
	private:
		sf::Sprite					_sprite;
		AircraftType				_type;
		TextNode*					_healthDisplay;
		TextNode*					_missileDisplay;

	};
}

