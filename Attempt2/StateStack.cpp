#include "StateStack.h"
#include <assert.h>

GEX::StateStack::StateStack(State::Context context) :_stack(), _pendingList(), _context(context), _factories() {}

void GEX::StateStack::update(sf::Time dt)
{
	for (auto itr = _stack.rbegin(); itr != _stack.rend(); itr++) {
		if (!(*itr)->update(dt))
			break;
	}
}

void GEX::StateStack::draw()
{
	for (State::Ptr & state : _stack)
		state->draw();
}

void GEX::StateStack::handleEvent(const sf::Event & event)
{
	for (auto itr = _stack.rbegin(); itr != _stack.rend(); itr++) {
		if ((*itr)->handleEvents(event) == false)
			break;
	}
	applyPendingChanges();
}

void GEX::StateStack::pushState(GEX::StateID stateID)
{
	_pendingList.push_back(PendingChange(Action::Push, stateID));
}

void GEX::StateStack::popState()
{
	_pendingList.push_back(PendingChange(Action::Pop));
}

void GEX::StateStack::clearStates()
{
	_pendingList.push_back(PendingChange(Action::Clear));
}

bool GEX::StateStack::isEmpty() const
{
	return _stack.empty();
}

GEX::State::Ptr GEX::StateStack::createState(GEX::StateID stateID)
{
	auto found = _factories.find(stateID);
	assert(found != _factories.end());
	return found->second();
}

void GEX::StateStack::applyPendingChanges()
{
	for (PendingChange change : _pendingList) {
		switch (change.action) {
		case Action::Push:
			_stack.push_back(createState(change.stateID));
			break;
		case Action::Pop:
			_stack.pop_back();
			break;
		case Action::Clear:
			_stack.clear();
			break;
		}
	}
	_pendingList.clear();
}

GEX::StateStack::PendingChange::PendingChange(Action action, StateID stateID):action(action),stateID(stateID)
{
}
