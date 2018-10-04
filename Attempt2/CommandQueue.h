/*
*@author: Greg VanKampen
*@file: CommandQueue.h
*@description: Queue of commands that can push and pop
*/

#pragma once
#include "Command.h"
#include <queue>

namespace GEX {
	//forward declaration
	class CommandQueue
	{
	public:
		void push(const Command& command);
		Command pop();
		bool isEmpty() const;
	private:
		std::queue<Command>		_queue;
	};

}

