#ifndef WORLD_HPP
#define WORLD_HPP

#include "Entity.hpp"
#include "Event.hpp"
#include "System.hpp"
#include <memory>
#include <string>
#include <vector>

namespace SimpleECS
{
    // The World class manages the creation and destruction of the entities
    class World
    {

    public:
        World();

        EntityManager &GetEntityManager() const;
        SystemManager &GetSystemManager() const;
        EventManager &GetEventManager() const;

        void Update();

        Entity CreateEntity();
        void DestroyEntity(Entity e);
        Entity GetEntity(std::string tag) const;
        std::vector<Entity> GetGroup(std::string group) const;

    private:
        // Vector of entities awaiting creation
        std::vector<Entity> m_createdEntities;

        // Vector of entities awaiting destruction
        std::vector<Entity> m_destroyedEntities;

        std::unique_ptr<EntityManager> m_entityManager = nullptr;
        std::unique_ptr<SystemManager> m_systemManager = nullptr;
        std::unique_ptr<EventManager> m_eventManager = nullptr;
    };

} // namespace SimpleECS

#endif