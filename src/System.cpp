#include "System.hpp"
#include "World.hpp"
#include <algorithm>

namespace SimpleECS
{
    void System::AddEntity(Entity e)
    {
        m_entities.push_back(e);
    }

    void System::RemoveEntity(Entity e)
    {
        m_entities.erase(std::remove_if(
                             m_entities.begin(), m_entities.end(),
                             [&e](Entity other)
                             { return e == other; }),
                         m_entities.end());
    }

    World &System::GetWorld() const
    {
        return *m_world;
    }

    void SystemManager::AddToSystems(Entity e)
    {
        const auto &entityComponentMask = m_world.GetEntityManager().GetComponentMask(e);

        for (auto &it : m_systems)
        {
            auto &system = it.second;
            const auto &systemComponentMask = system->GetComponentMask();
            auto interest = (entityComponentMask & systemComponentMask) == systemComponentMask;

            if (interest)
            {
                system->AddEntity(e);
            }
        }
    }

    void SystemManager::RemoveFromSystems(Entity e)
    {
        for (auto &it : m_systems)
        {
            auto &system = it.second;
            system->RemoveEntity(e);
        }
    }

}