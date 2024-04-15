#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Component.hpp"
#include "Config.hpp"
#include "Pool.hpp"

#include <deque>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

namespace SimpleECS
{
    class World;
    class EntityManager;

    class Entity
    {
    public:
        Entity(IdType id) : m_id{id} {};
        Entity(const Entity &) = default;
        Entity &operator=(const Entity &) = default;

        IdType GetId() const { return m_id; }
        void Kill();
        bool IsAlive() const;

        bool operator==(const Entity &e) const { return GetId() == e.GetId(); }
        bool operator!=(const Entity &e) const { return GetId() != e.GetId(); }
        bool operator<(const Entity &e) const { return GetId() < e.GetId(); }
        bool operator>(const Entity &e) const { return GetId() > e.GetId(); }

        /* Component management */
        template <typename T>
        void AddComponent(T component);
        template <typename T, typename... Args>
        void AddComponent(Args &&...args);
        template <typename T>
        void RemoveComponent() const;
        template <typename T>
        bool HasComponent() const;
        template <typename T>
        T &GetComponent() const;

        /* Tags the entity */
        void Tag(std::string tag);
        bool HasTag(std::string tag) const;

        /* Adds the entity to a certains group */
        void Group(std::string group);
        void HasGroup(std::string group) const;

    private:
        IdType m_id;
        EntityManager *m_entityManager = nullptr;
    };

    class EntityManager
    {
    public:
        EntityManager(World &world) : m_world{world} {};

        /* Entity management */
        Entity CreateEntity();
        void DestroyEntity(Entity e);
        void KillEntity(Entity e);
        bool IsEntityAlive(Entity e) const;
        Entity GetEntity(IdType entittyId);

        /* Component management */
        template <typename T>
        void AddComponent(Entity e, T component);
        template <typename T, typename... Args>
        void AddComponent(Entity e, Args &&...args);
        template <typename T>
        void RemoveComponent(Entity e);
        template <typename T>
        bool HasComponent(Entity e) const;
        template <typename T>
        T &GetComponent(Entity e) const;

        /* Tag management */
        void TagEntity(Entity e, std::string tag);
        bool HasTag(std::string tag) const;
        bool HasTaggedEntity(std::string tag, Entity e) const;
        Entity GetEntityByTag(std::string tag);

        /* Groupü management */
        void GroupEntity(Entity e, std::string group);
        bool HasGroup(std::string group) const;
        bool HasEntityInGroup(std::string group, Entity e) const;
        std::vector<Entity> GetEntityGroup(std::string group);

    private:
        std::vector<std::shared_ptr<AbstractPool>> componentPools;
        std::vector<ComponentMask> componentMasks;
        std::deque<IdType> freeIds;

        std::unordered_map<std::string, Entity> taggedEntities;
        std::unordered_map<IdType, std::string> entityTags;

        std::unordered_map<std::string, std::set<Entity>> groupedEntities;
        std::unordered_map<IdType, std::string> entityGroups;

        World &m_world;
    };

    template <typename T>
    void Entity::AddComponent(T component)
    {
        m_entityManager->AddComponent<T>(*this, component);
    }

    template <typename T, typename... Args>
    void Entity::AddComponent(Args &&...args)
    {
        m_entityManager->AddComponent<T>(*this, std::forward<Args>(args)...);
    }

    template <typename T>
    void Entity::RemoveComponent() const
    {
        m_entityManager->RemoveComponent<T>(*this);
    }

    template <typename T>
    bool Entity::HasComponent() const
    {
        return m_entityManager->HasComponent<T>(*this);
    }

    template <typename T>
    T &Entity::GetComponent() const
    {
        return m_entityManager->GetComponent<T>(*this);
    }

    template <typename T>
    void EntityManager::AddComponent(Entity e, T component)
    {
        const auto componentId = Component<T>::GetId();
        const auto entityId = e.GetId();

        if (entityId >= componentPools.size())
        {
            componentPools.resize(componentId + 1, nullptr);
        }

        if (!componentPools[componentId])
        {
            std::shared_ptr<Pool<T>> newComponentPool = std::make_shared<Pool<T>>();
            componentPools[componentId] = newComponentPool;
        }

        std::shared_ptr<Pool<T>> componentPool = std::static_pointer_cast<Pool<T>>(componentPools[componentId]);
        componentPool->set(entityId, component);
        componentMasks[entityId].set(componentId);
    }

    template <typename T, typename... Args>
    void EntityManager::AddComponent(Entity e, Args &&...args)
    {
        T component(std::forward<Args>(args)...);
        AddComponent<T>(e, component);
    }

    template <typename T>
    void EntityManager::RemoveComponent(Entity e)
    {
        const auto componentId = Component<T>::GetId();
        const auto entityId = e.GetId();
        componentMasks[entityId] = set(componentId, false);
    }

    template <typename T>
    bool EntityManager::HasComponent(Entity e) const
    {
        const auto componentId = Component<T>::GetId();
        const auto entityId = e.GetId();
        return componentMasks[entityId].test(componentId);
    }
    template <typename T>
    T &EntityManager::GetComponent(Entity e) const
    {
        const auto componentId = Component<T>::GetId();
        const auto entityId = e.GetId();

        auto componentPool = std::static_pointer_cast<Pool<T>>(componentPools[componentId]);
        return componentPool->get(entityId);
    }
}

#endif