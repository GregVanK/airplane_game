#include "ParticleNode.h"



namespace GEX {

	namespace {
		const std::map<GEX::Particle::Type, GEX::ParticleData>TABLE = initalizeParticleData();
	}

	ParticleNode::ParticleNode(Particle::Type type,TextureManager& textures)
		:SceneNode(),
		_particles(),
		_texture(textures.get(GEX::TextureID::Particle)),
		_type(type),
		_vertexArray(sf::Quads),
		_needsVertexUpdate(true)
	{
	}

	void ParticleNode::addParticle(sf::Vector2f position)
	{
		Particle particle;
		particle.position = position;
		particle.color = TABLE.at(_type).color;
		particle.lifetime = TABLE.at(_type).lifetime;

		_particles.push_back(particle);
	}

	Particle::Type ParticleNode::getParticleType() const
	{
		return _type;
	}

	unsigned int ParticleNode::getCategory() const
	{
		return Category::ParticleSystem;
	}

	void ParticleNode::updateCurrent(sf::Time dt, CommandQueue & commands)
	{
		//remove dead particles
		while (!_particles.empty() && _particles.front().lifetime <= sf::Time::Zero)
			_particles.pop_front();

		//decrement lifespan
		for (Particle& p : _particles)
			p.lifetime -= dt;

		//marks for update
		_needsVertexUpdate = true;
	}

	void ParticleNode::drawcurrent(sf::RenderTarget & target, sf::RenderStates states) const
	{
		if (_needsVertexUpdate) {
			computeVerticies();
			_needsVertexUpdate = false;
		}
		states.texture = &_texture;

		//draw all verticies

		target.draw(_vertexArray, states);
	}

	void ParticleNode::addVertex(float worldX, float worldY, float texCoordU, float texCoordV, const sf::Color color) const
	{
		sf::Vertex vertex;
		vertex.position = sf::Vector2f(worldX, worldY);
		vertex.texCoords = sf::Vector2f(texCoordU, texCoordV);
		vertex.color = color;

		_vertexArray.append(vertex);

	}

	void ParticleNode::computeVerticies() const
	{
		sf::Vector2f size(_texture.getSize());
		sf::Vector2f half = size / 2.f;

		_vertexArray.clear();
		//refill vertex array;
		for (const Particle& p : _particles) {
			sf::Vector2f pos = p.position;
			sf::Color color = p.color;
			
			float ratio = p.lifetime.asSeconds() / TABLE.at(_type).lifetime.asSeconds();
			color.a = static_cast<sf::Uint8>(255 * std::max(ratio,0.f));
			addVertex(pos.x - half.x, pos.y - half.y, 0.f, 0.f, color);
			addVertex(pos.x + half.x, pos.y - half.y,size.x, 0.f, color);
			addVertex(pos.x + half.x, pos.y + half.y, size.x, size.y, color);
			addVertex(pos.x - half.x, pos.y + half.y, 0.f, size.y, color);
		}
	}

}
