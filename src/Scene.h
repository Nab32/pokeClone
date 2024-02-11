#pragma once
#include "EntityManager.h"
#include "Action.h"
#include "GameEngine.h"
#include <map>

class Scene
{
    public:
        Scene(GameEngine* game) { m_game = game; };
        virtual void update() = 0;
        virtual void sDoAction(const Action& action) = 0;
        virtual void sRender() = 0;


        void doAction(const Action& action)
        {
            sDoAction(action);
        }
        void registerAction(int key, const std::string& action);

        bool hasEnded() const { return m_hasEnded; }

        std::map<int, std::string>& getActionMap() { return m_actionMap; }
        
    protected:
        GameEngine* m_game;
        EntityManager m_entities;
        virtual void onEnd() = 0;
        void setPaused(bool paused) { m_paused = paused; }
        int currentFrame = 0;
        std::map<int, std::string> m_actionMap;
        bool m_paused = false;
        bool m_hasEnded = false;
};