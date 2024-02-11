#include "Scene.h"
#include <string>
#include <memory>
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <vector>

class ScenePlay : public Scene
{
    public:
        ScenePlay(GameEngine* game, const std::string& path);
        void init();
        void loadLevel();
        void onEnd() override;
        void update() override;
        void loadCollision();
        void spawnPlayer();
        void sDoAction(const Action& action) override;
        void sRender() override;
        void sCollision();
        void sAnimation();
        void sMovement();
        void sCamera();
        void sInteract();
        void sDialogue(std::vector<std::string> dialogue);
        void queueDialogue();
        void loadInteractables();
        void loadDecorations();
        void generateTextbox(std::string text);
        Vec2 getPosition(Vec2 grid);
        std::string findStringtoPrint(std::shared_ptr<Entity> entity);
    protected:
        std::string m_path;
        int gameScale = 3;
        sf::Sound m_sound;
        std::shared_ptr<Entity> m_map;
        std::shared_ptr<Entity> m_player;
        std::vector<std::string> m_dialogue = {};
        int currentDialogue = 0;
        std::shared_ptr<Entity> m_currentTextbox = nullptr;
        sf::View m_view;
        int m_cameraYOffset = 32;
};