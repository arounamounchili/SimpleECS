#ifndef POOL_HPP
#define POOL_HPP

#include <vector>

#include "Config.hpp"

namespace SimpleECS
{
    // Requires to have a vector pools containing different object types
    class BasePool
    {
    public:
        virtual ~BasePool() = default;
        virtual void clear() = 0;
    };

    // A Pool is just a vector (contiguous data) of objects of type T
    template <typename T>
    class Pool : public BasePool
    {
    public:
        Pool(int capacity = 100) { Resize(capacity); }

        virtual ~Pool() = default;

        bool IsEmpty() const { return m_data.empty(); }

        unsigned int GetSize() const { return m_data.site(); }

        void Resize(int n) { m_data.resize(n); }

        void Set(EntityIdType entittyId, T object) { m_data[entittyId] = object; }

        T &Get(EntityIdType entityId) { return static_cast<T &>(m_data[entityId]); }

        void Add(T object) { m_data.push_back(object); }

        T &operator[](EntityIdType entityId) { return m_data[entityId]; }

        const T &operator[](EntityIdType entityId) const { return m_data[entityId]; }

        std::vector<T> GetData() { return m_data; }

        void clear() override { m_data.clear(); }

    private:
        std::vector<T> m_data;
    };
} // namespace SimpleECS

#endif