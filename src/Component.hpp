#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "Config.hpp"
#include <bitset>

namespace SimpleECS
{
    // Used to be able to assign unique ids to each component type
    struct BaseComponent
    {
    protected:
        static componentIdType nextId;
    };

    // Used to assign a unique id to a component type
    template <typename T>
    struct Component : BaseComponent
    {
        // Returns the unique id of Component<T>
        static componentIdType GetId()
        {
            static auto id = nextId++;
            return id;
        }
    };

    // Used to keep track of which components an entity has and also which
    // entities a system is interested in
    using ComponentMask = std::bitset<MAX_COMPONENTS>;
}

#endif