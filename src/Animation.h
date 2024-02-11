#pragma once

#include "vector2D.h"
#include <SFML/Graphics.hpp>

class Animation
{
    public:
        Animation() {}
        Animation(int frameCount, int speed, const std::string& name, const sf::Texture& texture);
        void update();
        void hasEnded();
        std::string& getName();
        void setFrame(int frame);
        Vec2& getSize();
        sf::Sprite& getSprite();
    private:
        sf::Sprite m_sprite;
        int m_frameCount;
        int m_currentFrame;
        int m_speed;
        Vec2 m_size;
        std::string m_name;
};