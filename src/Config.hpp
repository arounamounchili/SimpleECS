#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <iostream>

namespace SimpleECS
{
    using EntityIdType = uint32_t;
    using ComponentIdType = uint8_t;
    using EventIdType = uint8_t;

    enum
    {
        MAX_COMPONENTS = 64,
        DEFAULT_POOL_SIZE = 100
    };

} // namespace SimpleECS

#endif