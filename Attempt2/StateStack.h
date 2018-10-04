#pragma once
#include "StateIdentifiers.h"
#include "State.h"
#include<functional>
namespace sf {
	class Event;
	class RenderWindow;
}
namespace GEX {
	class StateStack
	{
	public:
		enum class Action {
			Push,
			Pop,
			Clear
		};
		explicit StateStack(State::Context context);
		template <typename T>
		void					registerState(GEX::StateID stateID);
		void					update(sf::Time dt);
		void					draw();
		void					handleEvent(const sf::Event& event);
		void					pushState(GEX::StateID stateID);
		void					popState();
		void					clearStates();
		bool					isEmpty() const;
	private:
		State::Ptr				createState(GEX::StateID stateID);
		void					applyPendingChanges();
	private:
		struct PendingChange {
			explicit PendingChange(Action action, StateID stateID = GEX::StateID::None);
			Action action;
			GEX::StateID stateID;
		};
	private:
		std::vector<State::Ptr> _stack;
		std::vector<PendingChange> _pendingList;
		State::Context _context;
		std::map <GEX::StateID, std::function<State::Ptr()>> _factories;
	};
	template <typename T>
	void StateStack::registerState(GEX::StateID stateID) {
		_factories[stateID] = [this]() {
			return State::Ptr(new T(*this, _context));
		};
	}
}

