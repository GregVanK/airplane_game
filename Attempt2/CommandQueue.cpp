/*
*@author: Greg VanKampen
*@file: CommandQueue.cpp
*@description: Queue of commands that can push and pop
*/
#include "CommandQueue.h"

namespace GEX {



	void CommandQueue::push(const Command & command)
	{
		_queue.push(command);
	}

	Command CommandQueue::pop()
	{
		auto temp = _queue.front();
		_queue.pop();
		return temp;
	}

	bool CommandQueue::isEmpty() const
	{
		return _queue.empty();
	}

}