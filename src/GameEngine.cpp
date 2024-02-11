#include "GameEngine.h"
#include "Scene.h"
#include "ScenePlay.h"
#include <iostream>

GameEngine::GameEngine(const std::string& path)
{
    m_path = path;
    init();
}

void GameEngine::init()
{
    m_assets.loadAll("assets/loadAssets.txt");
    m_window.create(sf::VideoMode(1280, 720), "pokeClone");
    m_window.setFramerateLimit(60);

    m_currentScene = new ScenePlay(this, "littleroot.txt"); 
}

void GameEngine::update()
{
    m_currentScene->update();
    m_window.display();
}

void GameEngine::run()
{
    while (m_running)
    {
        update();
        sUserInput();
    }
}

void GameEngine::quit()
{
    
}

void GameEngine::changeScene(Scene* scene)
{
    m_currentScene = scene;
}

Assets& GameEngine::getAssets()
{
    return m_assets;
}

sf::RenderWindow& GameEngine::getWindow()
{
    return m_window;
}

Scene* GameEngine::getScene(const std::string& name)
{
    return m_scenes[name];
}

void GameEngine::addScene(const std::string& name, Scene* scene)
{
    m_scenes[name] = scene;
}

SceneMap& GameEngine::getScenes()
{
    return m_scenes;
}

void GameEngine::sUserInput()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_running = false;
        }
        if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
        {
            if (m_currentScene->getActionMap().find(event.key.code) != m_currentScene->getActionMap().end())
            {   
                std::string actionType = (event.type == sf::Event::KeyPressed) ? "START" : "END";
                m_currentScene->doAction(Action(m_currentScene->getActionMap()[event.key.code], actionType));
            }
        }
    }
}
