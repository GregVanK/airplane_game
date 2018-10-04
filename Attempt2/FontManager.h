/*
*@author: Greg VanKampen
*@file: FontManager.h
*@desc: 
*/
#pragma once
#include <map>
#include <memory>
#include <string>

#include "ResourceIdentifiers.h"
#include <SFML/Graphics/Font.hpp>

namespace GEX {
	class FontManager
	{
	private:
		FontManager() = default;
	public:
		static FontManager&			getInstance();
		void						load(FontID id, const std::string& path);
		sf::Font&					getFont(FontID id) const;
	private:
		static FontManager*			_instance;
		std::map < FontID, std::unique_ptr<sf::Font>> _fonts;
	};
}

