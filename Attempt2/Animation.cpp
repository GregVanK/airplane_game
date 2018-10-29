#include "Animation.h"
GEX::Animation::Animation()
	:_sprite(),
	_frameSize(),
	_numberOfFrames(0),
	_currentFrame(0),
	_duration(sf::Time::Zero),
	_elapsedTime(sf::Time::Zero),
	_repeat(false)
{

}

GEX::Animation::Animation(const sf::Texture & texture)
:_sprite(texture),
_frameSize(),
_numberOfFrames(0),
_currentFrame(0),
_duration(sf::Time::Zero),
_elapsedTime(sf::Time::Zero),
_repeat(false)
{
}

void GEX::Animation::setTexture(const sf::Texture & texture)
{
	_sprite.setTexture(texture);
}

const sf::Texture* GEX::Animation::getTexture() const
{
	return _sprite.getTexture();
}

void GEX::Animation::setFrameSize(sf::Vector2i framesize)
{
	_frameSize = framesize;
}

sf::Vector2i GEX::Animation::getFrameSize() const
{
	return _frameSize;
}

void GEX::Animation::setNumFrames(std::size_t numFrames)
{
	_numberOfFrames = numFrames;
}

std::size_t GEX::Animation::getNumFrames() const
{
	return _numberOfFrames;
}

void GEX::Animation::setDuration(sf::Time duration)
{
	_duration = duration;
}

sf::Time GEX::Animation::getDuration() const
{
	return _duration;
}

void GEX::Animation::setRepeating(bool flag)
{
	_repeat = flag;
}

bool GEX::Animation::isRepeating() const
{
	return _repeat;
}

sf::FloatRect GEX::Animation::getLocalBounds() const
{
	return sf::FloatRect(getOrigin(),static_cast<sf::Vector2f>(getFrameSize()));
}

sf::FloatRect GEX::Animation::getGlobalBounds() const
{
	return getTransform().transformRect(getLocalBounds());
}

void GEX::Animation::restart()
{
	_currentFrame = 0;
}

bool GEX::Animation::isFinished() const
{
	return _currentFrame >= _numberOfFrames;
}

void GEX::Animation::update(sf::Time dt)
{
	sf::Time timePerFrame = _duration / static_cast<float>(_numberOfFrames);
	_elapsedTime += dt;
	sf::Vector2i textureBounds(_sprite.getTexture()->getSize());
	sf::IntRect textureRect = _sprite.getTextureRect();

	if (_currentFrame == 0) {
		textureRect = sf::IntRect(0, 0, _frameSize.x, _frameSize.y);
	}
	while (_elapsedTime >= timePerFrame && (_currentFrame <= _numberOfFrames || _repeat)) {
		// move to next frame
		textureRect.left += textureRect.width;
		//go to next row 
		if (textureRect.left + textureRect.width > textureBounds.x) {
			textureRect.left = 0;
			textureRect.top += textureRect.height;
		}
		_elapsedTime -= timePerFrame;
		if (_repeat) {
			_currentFrame = (_currentFrame + 1) % _numberOfFrames;
			if (_currentFrame == 0) {
				textureRect = sf::IntRect(0, 0, _frameSize.x, _frameSize.y);
			}
		}
		else
		{
			_currentFrame++;
		}
	}
	_sprite.setTextureRect(textureRect);
}

void GEX::Animation::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(_sprite, states);
}



