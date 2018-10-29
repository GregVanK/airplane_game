#pragma once
#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics\Transformable.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\System\Time.hpp>
#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\Graphics\RenderStates.hpp>
namespace sf {
	class Time;
}
namespace GEX {
	class Animation : public sf::Drawable, public sf::Transformable
	{
	public:
		Animation();
		Animation(const sf::Texture& texture);

		void setTexture(const sf::Texture& texture);
		const sf::Texture* getTexture()const;
		void	setFrameSize(sf::Vector2i framesize);
		sf::Vector2i	getFrameSize() const;
		void			setNumFrames(std::size_t numFrames);
		std::size_t		getNumFrames() const;
		void			setDuration(sf::Time duration);
		sf::Time		getDuration() const;
		void			setRepeating(bool flag);
		bool			isRepeating()const;
		sf::FloatRect	getLocalBounds() const;
		sf::FloatRect	getGlobalBounds() const;

		void			restart();
		bool			isFinished() const;

		void			update(sf::Time dt);

	private:
		void	draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	private:
		sf::Sprite		_sprite;
		sf::Vector2i	_frameSize;
		std::size_t		_numberOfFrames;
		std::size_t		_currentFrame;
		sf::Time		_duration;
		sf::Time		_elapsedTime;
		bool			_repeat;
	};
}

