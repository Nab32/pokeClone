#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Animation.h"

class Assets
{
    public:
        Assets() {}
        void loadAll(const std::string& path);
        void addTexture(const std::string& name, const std::string& path);
        void addAnimation(const std::string& name, int frameCount, int speed, const std::string& path);
        void addSound(const std::string& name, const std::string& path);
        void addFont(const std::string& name, const std::string& path);

        sf::Texture& getTexture(const std::string& name);
        Animation& getAnimation(const std::string& name);
        sf::Sound* getSound(const std::string& name);
        sf::Font& getFont(const std::string& name);
    private:
        std::map<std::string, sf::Texture> m_textures;
        std::map<std::string, Animation> m_animations;
        std::map<std::string, sf::Sound*> m_sounds;
        std::map<std::string, sf::Font> m_fonts;
};