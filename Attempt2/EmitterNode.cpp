#include "EmitterNode.h"
#include "CommandQueue.h"
#include "Command.h"

GEX::EmitterNode::EmitterNode(Particle::Type type)
	:SceneNode(),
	_accumulatedTime(sf::Time::Zero),
	_type(type),
	_particleSystem(nullptr)
{
}

void GEX::EmitterNode::updateCurrent(sf::Time dt, CommandQueue & commands)
{
	if (_particleSystem) {
		emitParticle(dt);
	}
	else {

		auto finder = [this](ParticleNode& container,sf::Time dt) {
			if (container.getParticleType() == _type)
				_particleSystem = &container;
		};
		Command command;
		command.category = Category::ParticleSystem;
		command.action = derivedAction<ParticleNode>(finder);
		commands.push(command);
	}
}

void GEX::EmitterNode::emitParticle(sf::Time dt)
{
	const float EMISSION_RATE = 30.f;
	const sf::Time INTERVAL = sf::seconds(1.f) / EMISSION_RATE;
	_accumulatedTime += dt;
	while (_accumulatedTime > INTERVAL) {
		_accumulatedTime -= INTERVAL;
		_particleSystem->addParticle(getWorldPosition());
	}
}
