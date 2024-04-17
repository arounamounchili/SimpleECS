#include "World.hpp"

namespace SimpleECS
{
    World::World()
    {
        m_entityManager = std::make_unique<EntityManager>(*this);
        m_systemManager = std::make_unique<SystemManager>(*this);
        m_eventManager = std::make_unique<EventManager>(*this);
    }

    EntityManager &World::GetEntityManager() const
    {
        return *m_entityManager;
    }

    SystemManager &World::GetSystemManager() const
    {
        return *m_systemManager;
    }

    EventManager &World::GetEventManager() const
    {
        return *m_eventManager;
    }

    void World::Update()
    {
        for (auto e : m_createdEntities)
        {
            GetSystemManager().AddToSystems(e);
        }
        m_createdEntities.clear();

        for (auto e : m_destroyedEntities)
        {
            GetSystemManager().RemoveFromSystems(e);
            GetEntityManager().DestroyEntity(e);
        }

        m_destroyedEntities.clear();

        GetEventManager().DestroyEvents();
    }

    Entity World::CreateEntity()
    {
        auto e = GetEntityManager().CreateEntity();
        m_createdEntities.push_back(e);
        return e;
    }

    void World::DestroyEntity(Entity e)
    {
        m_destroyedEntities.push_back(e);
    }

    Entity World::GetEntity(std::string tag) const
    {
        return GetEntityManager().GetEntityByTag(tag);
    }

    std::vector<Entity> World::GetGroup(std::string group) const
    {
        return GetEntityManager().GetEntityGroup(group);
    }
}