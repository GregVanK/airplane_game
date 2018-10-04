#include "TextNode.h"
#include "Utility.h"
#include "FontManager.h"
#include <SFML/Graphics/RenderTarget.hpp>

GEX::TextNode::TextNode(const std::string & text)
{
	_text.setFont(GEX::FontManager::getInstance().getFont(GEX::FontID::Main));
	_text.setCharacterSize(20);
	setText(text);
}

void GEX::TextNode::setText(const std::string & text)
{
	_text.setString(text);
	centerOrigin(_text);
}


void GEX::TextNode::drawcurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(_text, states);
}
