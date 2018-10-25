#pragma once
#include "SceneNode.h"
#include "Particle.h"
#include "DataTables.h"
#include "TextureManager.h"
#include <deque>
#include "SFML\Graphics\VertexArray.hpp"
namespace GEX {

	

	class ParticleNode : public SceneNode
	{
	public:
		ParticleNode(Particle::Type type,TextureManager& textures);
		void addParticle(sf::Vector2f position);
		Particle::Type getParticleType() const;
		unsigned int	getCategory() const override;

	private:
		void	updateCurrent(sf::Time dt, CommandQueue& commands) override;
		void	drawcurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

		void	addVertex(float worldX, float worldY, float texCoordU, float texCoordV, const sf::Color color) const;
		void	computeVerticies() const;

	private:
		std::deque<Particle>		_particles;
		const sf::Texture&			_texture;
		Particle::Type				_type;

		mutable sf::VertexArray		_vertexArray;
		mutable bool				_needsVertexUpdate;
	};
}

