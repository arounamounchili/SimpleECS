#include "Entity.hpp"

namespace SimpleECS
{
    void Entity::Kill()
    {
        m_entityManager->KillEntity(*this);
    }

    void Entity::Tag(std::string tag)
    {
        m_entityManager->TagEntity(*this, tag);
    }

    bool Entity::HasTag(std::string tag) const
    {
        return m_entityManager->HasTaggedEntity(tag, *this);
    }

    void Entity::Group(std::string group)
    {
        m_entityManager->GroupEntity(*this, group);
    }

    bool Entity::HasGroup(std::string group) const
    {
        return m_entityManager->HasEntityInGroup(group, *this);
    }

    Entity EntityManager::CreateEntity()
    {
        EntityIdType entityId;
        if (m_freeIds.empty()) // if there is no free ids waiting to be used
        {
            entityId = m_numEntities++;
            if (entityId >= m_componentMasks.size())
            {
                m_componentMasks.resize(entityId + 1);
            }
        }
        else // Reuse an id from the list of free ids
        {
            entityId = m_freeIds.front();
            m_freeIds.pop_front();
        }
        Entity entity(entityId);
        entity.m_entityManager = this;

        return entity;
    }

    void EntityManager::DestroyEntity(Entity e)
    {
        const auto entityId = e.GetId();
        m_freeIds.push_back(entityId);
        m_componentMasks[entityId].reset();

        // if tagged, remove entity from tag management
        auto taggedEntity = m_entityTags.find(e.m_id);
        if (taggedEntity != m_entityTags.end())
        {
            auto tag = taggedEntity->second;
            m_taggedEntities.erase(tag);
            m_entityTags.erase(taggedEntity);
        }

        // if in group, remove entity from group management
        auto groupEntity = m_entityGroups.find(e.m_id);
        if (groupEntity != m_entityGroups.end())
        {
            auto groupName = groupEntity->second;
            auto group = m_groupedEntities.find(groupName);
            if (group != m_groupedEntities.end())
            {
                auto entityInGroup = group->second.find(e);
                if (entityInGroup != group->second.end())
                {
                    group->second.erase(entityInGroup);
                }
            }
            m_entityGroups.erase(groupEntity);
        }
    }

    void EntityManager::KillEntity(Entity e)
    {
        m_world.KillEntity();
    }

    void EntityManager::TagEntity(Entity e, std::string tag)
    {
        m_taggedEntities.emplace(tag, e);
        m_entityTags.emplace(e.m_id, tag);
    }
    bool EntityManager::HasTag(std::string tag) const
    {
        return m_taggedEntities.find(tag) != m_taggedEntities.end();
    }
    bool EntityManager::HasTaggedEntity(std::string tag, Entity e) const
    {
        auto it = m_taggedEntities.find(tag);
        if (it != m_taggedEntities.end())
        {
            if (it->second == e)
            {
                return true;
            }
        }
        return false;
    }

    Entity EntityManager::GetEntityByTag(std::string tag)
    {
        return m_taggedEntities[tag];
    }

    void EntityManager::GroupEntity(Entity e, std::string group)
    {
        m_groupedEntities.emplace(group, std::set<Entity>());
        m_groupedEntities[group].emplace(e);
        m_entityGroups.emplace(e.m_id, group);
    }

    bool EntityManager::HasGroup(std::string group) const
    {
        return m_groupedEntities.find(group) != m_groupedEntities.end();
    }

    bool EntityManager::HasEntityInGroup(std::string group, Entity e) const
    {
        auto it = m_groupedEntities.find(group);
        if (it != m_groupedEntities.end())
        {
            if (it->second.find(e.m_id) != it->second.end())
            {
                return true;
            }
        }
        return false;
    }

    std::vector<Entity> EntityManager::GetEntityGroup(std::string group)
    {
        auto &setOfEntities = m_groupedEntities[group];
        return std::vector<Entity>(setOfEntities.begin(), setOfEntities.end());
    }
}