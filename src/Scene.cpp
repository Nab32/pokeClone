#include "Scene.h"


void Scene::registerAction(int key, const std::string& action)
{
    m_actionMap[key] = action;
}

