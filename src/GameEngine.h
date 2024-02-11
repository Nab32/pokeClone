#pragma once
#include <memory>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <string>
#include "Assets.h"

class Scene;
class ScenePlay;

typedef std::map<std::string, Scene*> SceneMap;

class GameEngine
{
    public:
        GameEngine(const std::string& path);
        void init();
        void update();
        void run();
        void quit();
        void changeScene(Scene* scene);
        Assets& getAssets();
        sf::RenderWindow& getWindow();
        Scene* getScene(const std::string& name);
        void addScene(const std::string& name, Scene* scene);
        SceneMap& getScenes();
        void sUserInput();
    private:
        sf::RenderWindow m_window;
        std::string m_path;
        Assets m_assets;
        Scene* m_currentScene;
        bool m_running = true;
        sf::View m_view;
        SceneMap m_scenes;
};