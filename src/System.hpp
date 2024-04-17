#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "Entity.hpp"
#include "Event.hpp"
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace SimpleECS
{
    class SystemManager;
    class World;

    class System
    {
    public:
        System() = default;
        ~System() = default;

        template <typename T>
        void requireComponent();

        std::vector<Entity> GetEntities() { return m_entities; }
        void AddEntity(Entity e);
        // Remove the entity if it is not alive anymore(during processing)
        void RemoveEntity(Entity e);
        const ComponentMask &GetComponentMask() const { return m_componentMask; }

    protected:
        World &GetWorld() const;

    private:
        // Which components an entity must have in order for the system to process the entity
        ComponentMask m_componentMask;

        // Vector of all entities that the system is interested in
        std::vector<Entity> m_entities;

        World *m_world = nullptr;
        friend class SystemManager;
    };

    class SystemManager
    {
    public:
        SystemManager(World &world) : m_world{world} {}

        template <typename T>
        void AddSystem();
        template <typename T, typename... Args>
        void AddSystem(Args &&...args);
        template <typename T>
        void RemoveSystem();
        template <typename T>
        T &GetSystem();
        template <typename T>
        bool HasSystem() const;

        // Add an entity to each system that is insterested of the entity
        void AddToSystems(Entity e);
        // Removes an entity from interested system's entity class
        void RemoveFromSystems(Entity e);

    private:
        std::unordered_map<std::type_index, std::shared_ptr<System>> m_systems;
        World &m_world;
    };

    template <typename T>
    void System::requireComponent()
    {
        const auto componentId = Component<T>::GetId();
        m_componentMask.set(componentId);
    }

    template <typename T>
    void SystemManager::AddSystem()
    {
        if (HasSystem<T>())
        {
            return;
        }

        std::shared_ptr<T> system = std::make_shared<T>();
        system->m_world = &m_world;
        m_systems.insert(std::make_pair(std::type_index(typeid(T)), system));
    }

    template <typename T, typename... Args>
    void SystemManager::AddSystem(Args &&...args)
    {
        if (HasSystem<T>())
        {
            return;
        }

        std::shared_ptr<T> system = std::make_shared<T>(std::forward<Args>(args)...);
        system->m_world = &m_world;
        m_systems.insert(std::make_pair(std::type_index(typeid(T)), system));
    }

    template <typename T>
    void SystemManager::RemoveSystem()
    {
        if (!HasSystem<T>())
        {
            return;
        }

        auto it = m_systems.find(std::type_index(typeid(T)));
        m_systems.erase(it);
    }

    template <typename T>
    T &SystemManager::GetSystem()
    {
        if (!HasSystem<T>())
        {
            return;
        }

        auto it = m_systems.find(std::type_index(typeid(T)));
        return *(std::static_pointer_cast<T>(it->second));
    }

    template <typename T>
    bool SystemManager::HasSystem() const
    {
        return m_systems.find(std::type_index(typeid(T))) != m_systems.end();
    }

} // namespace SimpleECS

#endif