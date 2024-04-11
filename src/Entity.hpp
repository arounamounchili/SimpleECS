#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <iostream>

using IdType = uint32_t;

class Entity
{
public:
    Entity(IdType id) : m_id{id} {};
    Entity(const Entity &) = default;
    Entity &operator=(const Entity &) = default;

    IdType getId() const { return m_id; }

    bool operator==(const Entity &e) const { return getId() == e.getId(); }
    bool operator!=(const Entity &e) const { return getId() != e.getId(); }
    bool operator<(const Entity &e) const { return getId() < e.getId(); }
    bool operator>(const Entity &e) const { return getId() > e.getId(); }

private:
    IdType m_id;
};

#endif