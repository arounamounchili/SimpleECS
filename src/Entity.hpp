#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Config.hpp"
#include "Pool.hpp"

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

        // Component management
        template <typename T, typename... Args>
        void AddComponent(Args &&...args);
        template <typename T>
        void RemoveComponent() const;
        template <typename T>
        bool HasComponent() const;
        template <typename T>
        T &GetComponent() const;

    private:
        IdType m_id;
        EntityManager *entityManager = nullptr;
    };

    class EntityManager
    {
    public:
        EntityManager(World &world) : m_world{world} {};

    private:
        World &m_world;
    };

    template <typename T, typename... Args>
    void Entity::AddComponent(Args &&...args)
    {
    }

    template <typename T>
    void Entity::RemoveComponent() const
    {
    }

    template <typename T>
    bool Entity::HasComponent() const
    {
    }

    template <typename T>
    T &Entity::GetComponent() const
    {
    }
}

#endif