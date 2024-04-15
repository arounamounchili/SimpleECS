#include "Entity.hpp"

namespace SimpleECS
{
    void Entity::Kill()
    {
    }

    bool Entity::IsAlive() const
    {
    }

    void Entity::Tag(std::string tag)
    {
    }

    bool Entity::HasTag(std::string tag) const
    {
    }

    void Entity::Group(std::string group)
    {
    }

    void Entity::HasGroup(std::string group) const
    {
    }

    Entity EntityManager::CreateEntity()
    {
    }
    void EntityManager::DestroyEntity(Entity e)
    {
    }
    void EntityManager::KillEntity(Entity e)
    {
    }
    bool EntityManager::IsEntityAlive(Entity e) const
    {
    }
    Entity EntityManager::GetEntity(EntityIdType entittyId)
    {
    }

    void EntityManager::TagEntity(Entity e, std::string tag)
    {
    }
    bool EntityManager::HasTag(std::string tag) const
    {
    }
    bool EntityManager::HasTaggedEntity(std::string tag, Entity e) const
    {
    }
    Entity EntityManager::GetEntityByTag(std::string tag)
    {
    }

    void EntityManager::GroupEntity(Entity e, std::string group)
    {
    }
    bool EntityManager::HasGroup(std::string group) const
    {
    }
    bool EntityManager::HasEntityInGroup(std::string group, Entity e) const
    {
    }
    std::vector<Entity> EntityManager::GetEntityGroup(std::string group)
    {
    }
}