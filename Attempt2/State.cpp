#include "State.h"
#include "StateStack.h"
namespace GEX {
	State::State(StateStack & stack, Context context):_stack(&stack),_context(context)
	{
	}
	State::~State()
	{
	}
	void State::requestStackPush(StateID stateID)
	{
		_stack->pushState(stateID);
	}
	void State::requestStackPop()
	{
		_stack->popState();
	}
	void State::requestStackClear()
	{
		_stack->clearStates();
	}
	State::Context State::getContext() const
	{
		return _context;
	}
	
	State::Context::Context(sf::RenderWindow & window, TextureManager & textures, sf::Font & font, PlayerControl & player):window(&window), textures(&textures),player(&player) //RE INITALIZE
	{
	}

}