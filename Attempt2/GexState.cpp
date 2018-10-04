/*
*@author: Greg VanKampen
*@file: GameState.h
*@description: The state of the application when the game is running
*/
#include "GexState.h"
#include "Utility.h"
#include "FontManager.h"



GexState::GexState(GEX::StateStack & stack, Context context)
	:State(stack, context),
	_backgroundSprite(),
	_pausedText(),
	_gexText(),
	_returnText(),
	_exitText()
{
	//set up paused text
	_pausedText.setFont(GEX::FontManager::getInstance().getFont(GEX::FontID::Main));
	_pausedText.setString("Game Paused");
	_pausedText.setCharacterSize(30);
	centerOrigin(_pausedText);
	
	//set up Gex state text
	_gexText.setFont(GEX::FontManager::getInstance().getFont(GEX::FontID::Main));
	_gexText.setString("Gex State");
	_gexText.setCharacterSize(50);
	centerOrigin(_gexText);

	//set up return instructions text
	_returnText.setFont(GEX::FontManager::getInstance().getFont(GEX::FontID::Main));
	_returnText.setString("Press G to return to the game");
	_returnText.setCharacterSize(30);
	centerOrigin(_returnText);

	//set up exit instructions text
	_exitText.setFont(GEX::FontManager::getInstance().getFont(GEX::FontID::Main));
	_exitText.setString("Press Backspace to return to the main menu");
	_exitText.setCharacterSize(30);
	centerOrigin(_exitText);

	//position text objects
	sf::Vector2f viewSize = context.window->getView().getSize();
	_pausedText.setPosition(0.5f * viewSize.x, 0.3f * viewSize.y);
	_gexText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);
	_returnText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);
	_exitText.setPosition(0.5f * viewSize.x, 0.7f * viewSize.y);

	//load bg texture
	sf::Texture& texture = context.textures->get(GEX::TextureID::GexScreen);
	_backgroundSprite.setTexture(texture);
}
//Draws the objects in the window
void GexState::draw()
{
	//capture window
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	//draw objects
	window.draw(_backgroundSprite);
	sf::RectangleShape backgroundPane;
	backgroundPane.setFillColor(sf::Color(255, 0, 0, 100));
	backgroundPane.setSize(window.getView().getSize());
	window.draw(backgroundPane);
	window.draw(_pausedText);
	window.draw(_gexText);
	window.draw(_returnText);
	window.draw(_exitText);
}
//tell the application to not update
bool GexState::update(sf::Time dt)
{
	return false;
}
//checks for keypress events
bool GexState::handleEvents(const sf::Event & event)
{
	if (event.type != sf::Event::KeyPressed)
		return false;

	if (event.key.code == sf::Keyboard::G)//Continue game if G is pressed
		requestStackPop();
	if (event.key.code == sf::Keyboard::BackSpace)//Return to menu
	{
		requestStackClear();
		requestStackPush(GEX::StateID::Menu);
	}
	return false;
}
