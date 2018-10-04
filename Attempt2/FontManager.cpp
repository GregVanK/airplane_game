#include "FontManager.h"
#include <assert.h>

namespace GEX {
	FontManager* FontManager::_instance = nullptr;
	FontManager & FontManager::getInstance()
	{
		if (!_instance)
			FontManager::_instance = new FontManager();
		return *FontManager::_instance;
	}
	void FontManager::load(FontID id, const std::string & path)
	{
		std::unique_ptr<sf::Font> font(new sf::Font);
		if (!font->loadFromFile(path))
			throw std::runtime_error("Font file missing");
		auto rc = _fonts.insert(std::make_pair(id, std::move(font)));
		if (!rc.second)
			assert(0); //WHERE FONT?!
	}
	sf::Font & FontManager::getFont(FontID id) const
	{
		auto found = _fonts.find(id);
		assert(found != _fonts.end());
		return *found->second;
	}
}