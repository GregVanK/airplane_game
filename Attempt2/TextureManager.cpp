#include "TextureManager.h"





GEX::TextureManager::TextureManager()
{
}

GEX::TextureManager::~TextureManager()
{
}

void GEX::TextureManager::load(TextureID id, const std::string & path)
{
	std::unique_ptr <sf::Texture> loadedTexture(new sf::Texture());
	if (!loadedTexture->loadFromFile(path))
	{
		throw std::runtime_error("Texture Load Failure:" + path);
	}
	auto rc = _textures.insert(std::make_pair(id, std::move(loadedTexture)));
	assert(rc.second);
}

sf::Texture& GEX::TextureManager::get(TextureID id) const
{
	auto found = _textures.find(id);
	assert(found != _textures.end());
	return *(found->second);
}
