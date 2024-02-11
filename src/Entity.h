#pragma once

#include <memory>
#include <string>
#include "Components.h"

class Entity
{
    public:
        std::shared_ptr<CTransform> cTransform;
        std::shared_ptr<CAnimation> cAnimation;
        std::shared_ptr<CBoundingBox> cBoundingBox;
        std::shared_ptr<CInput> cInput;
        std::shared_ptr<CState> cState;
        std::shared_ptr<CInteract> cInteract;
        std::shared_ptr<CText> cText;
        std::shared_ptr<CLifespan> cLifespan;

        bool isAlive() const;
        const std::string& tag() const;
        const size_t id() const;
        void destroy();
    private:
        friend class EntityManager;

        bool m_alive = true;
        size_t m_id = 0;
        std::string m_tag = "default";
        Entity(const size_t id, const std::string& tag);
};