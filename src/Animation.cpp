#include "Animation.h"
#include <iostream>

Animation::Animation(int frameCount, int speed, const std::string& name, const sf::Texture& texture)
    :   m_frameCount(frameCount),
        m_speed(speed),
        m_name(name),
        m_currentFrame(0)
{
    m_size = Vec2((float)texture.getSize().x / frameCount, (float)texture.getSize().y);
    m_sprite.setTexture(texture);
    m_sprite.setTextureRect(sf::IntRect(0, 0, m_size.x, m_size.y));
}

void Animation::update()
{
    m_currentFrame++;
    int animFrame = (m_currentFrame / m_speed) % m_frameCount;
    m_sprite.setTextureRect(sf::IntRect(animFrame * m_size.x, 0, m_size.x, m_size.y));
}

void Animation::setFrame(int frame)
{
    m_sprite.setTextureRect(sf::IntRect(frame * m_size.x, 0, m_size.x, m_size.y));
}

void Animation::hasEnded()
{
    
}

std::string& Animation::getName()
{
    return m_name;
}

Vec2& Animation::getSize()
{
    return m_size;
}

sf::Sprite& Animation::getSprite()
{
    return m_sprite;
}
