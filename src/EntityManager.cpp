#include "EntityManager.h"

EntityManager::EntityManager()
{
    
}

void EntityManager::update()
{
    m_entities.insert(m_entities.end(), m_toAdd.begin(), m_toAdd.end());

    removeDeadEntities(m_entities);

    for (auto it = m_entityMap.begin(); it != m_entityMap.end(); it++)
    {
        removeDeadEntities(it->second);
    }

    m_toAdd.clear();
}

//DONE:
// 1. Create a new entity with the next available id and the given tag.
// 2. Add the entity to the list of entities to be added.
// 3. Add the entity to the entity map.
// 4. Return the entity.
std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
    auto e = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));
    m_toAdd.push_back(e);
    m_entityMap[tag].push_back(e);
    return e;
}

EntityVec& EntityManager::getEntities()
{
    return m_entities;
}

EntityVec& EntityManager::getEntities(const std::string& tag)
{
    return m_entityMap[tag];
}

const std::map<std::string, EntityVec>& EntityManager::getEntityMap()
{
    return m_entityMap;
}

void EntityManager::removeDeadEntities(EntityVec& vec)
{
    vec.erase(std::remove_if(vec.begin(), vec.end(), [](std::shared_ptr<Entity> e) { return !e->isAlive(); }), vec.end());
}
