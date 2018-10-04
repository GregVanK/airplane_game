//
//Texture Manager
//manage game resources
#pragma once
#include <map>
#include <memory>
#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <assert.h>
#include "ResourceIdentifiers.h"
namespace GEX {
	
	class TextureManager
	{
	public:
		TextureManager();
		~TextureManager();
		void load(TextureID id, const std::string& path);
		sf::Texture& get(TextureID id) const;
	private:
		std::map<TextureID,std::unique_ptr<sf::Texture>> _textures;
	};
}

