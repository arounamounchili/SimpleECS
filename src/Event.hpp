#ifndef EVENT_H
#define EVENT_H

#include "Pool.hpp"
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace SimpleECS
{
    class World;

    struct BaseEvent
    {
    protected:
        static EventIdType nextId;
    };

    template <typename T>
    struct Event : BaseEvent
    {
        // Returns the unique id of the Event<T>
        static EventIdType GetId()
        {
            static auto id = nextId++;
            return id;
        }
    };

    class EventManager
    {
    public:
        EventManager(World &world) : m_world{world} {};

        template <typename T>
        void EmitEvent(T event);

        template <typename T, typename... Args>
        void EmitEvent(Args &&...args);

        template <typename T>
        std::vector<T> GetEvent();

        void DestroyEvents();

    private:
        std::unordered_map<std::type_index, std::shared_ptr<BasePool>> m_eventPools;
        World &m_world;
    };

    template <typename T>
    void EventManager::EmitEvent(T event)
    {
        if (m_eventPools.find(std::type_index(typeid(T))) == m_eventPools.end())
        {
            std::shared_ptr<Pool<T>> pool = std::make_shared<Pool<T>>();
            m_eventPools.insert(std::make_pair(std::type_index(typeid(T)), pool));
        }
        std::shared_ptr<Pool<T>> eventPool = std::static_pointer_cast<Pool<T>>(m_eventPools[std::type_index(typeid(T))]);
        eventPool->add(event);
    }

    template <typename T, typename... Args>
    void EventManager::EmitEvent(Args &&...args)
    {
        T event(std::forward<Args>(args)...);
        EmitEvent<T>(event);
    }

    template <typename T>
    std::vector<T> EventManager::GetEvent()
    {
        return std::static_pointer_cast<Pool<T>>(m_eventPools[std::type_index(typeid(T))]).getData();
    }

} // namespace SimpleECS

#endif