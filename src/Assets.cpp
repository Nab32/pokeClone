#include "Assets.h"
#include <iostream>

void Assets::addTexture(const std::string& name, const std::string& path)
{
    sf::Texture texture;
    if (texture.loadFromFile(path)) {
        m_textures[name] = texture;
    } else {
        // Handle error if texture loading fails
        std::cout << "Failed to load texture: " << path << "\n";
    }
}

void Assets::addAnimation(const std::string& name, int frameCount, int speed, const std::string& path)
{
    sf::Texture* texture = new sf::Texture();
    if (texture->loadFromFile(path)) {
        m_animations[name] = Animation(frameCount, speed, name, *texture);
    } else {
        // Handle error if texture loading fails
        std::cout << "Failed to load texture: " << path << "\n";
    }
}

void Assets::addSound(const std::string& name, const std::string& path)
{
    sf::SoundBuffer* buffer = new sf::SoundBuffer();
    if (buffer->loadFromFile(path)) {
        sf::Sound* sound = new sf::Sound();
        sound->setBuffer(*buffer);
        m_sounds[name] = sound;
    } else {
        // Handle error if sound loading fails
        std::cout << "Failed to load sound: " << path << "\n";
    }
}

sf::Texture& Assets::getTexture(const std::string& name)
{
    return m_textures[name];
}

Animation& Assets::getAnimation(const std::string& name)
{
    return m_animations[name];
}

sf::Sound* Assets::getSound(const std::string& name)
{
    return m_sounds[name];
}

void Assets::loadAll(const std::string& path)
{
    std::ifstream file(path);
    std::string line;

    if (!file.is_open()) {
        std::cout << "Failed to open file: " << path << "\n";
        return;
    }

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string type;
        std::string name;
        int frameCount;
        int speed;
        std::string path;

        if (!(iss >> type >> name >> frameCount >> speed >> path)) {
            std::cout << "Failed to parse line: " << line << "\n";
            continue;
        }

        if (type == "ANIMATION")
        {
            addAnimation(name, frameCount, speed, path);
        } 
        else if (type == "SOUND")
        {
            addSound(name, path);
        } 
        else if (type == "TEXTURE")
        {
            addTexture(name, path);
        }
        else if (type == "FONT")
        {
            addFont(name, path);
        }
    }
    file.close();
}

void Assets::addFont(const std::string& name, const std::string& path)
{
    sf::Font font;
    if (font.loadFromFile(path)) {
        m_fonts[name] = font;
    } else {
        // Handle error if font loading fails
        std::cout << "Failed to load font: " << path << "\n";
    }
}

sf::Font& Assets::getFont(const std::string& name)
{
    return m_fonts[name];
}