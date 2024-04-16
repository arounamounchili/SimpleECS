#include "Event.hpp"

namespace SimpleECS
{
    EventIdType BaseEvent::nextId = 0;

    void EventManager::DestroyEvents()
    {
        for (auto &it : m_eventPools)
        {
            auto pool = it.second;
            pool->clear();
        }
    }

}