#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <iostream>

using IdType = uint32_t;

class World;
class EntityManager;

class Entity {
 public:
  Entity(IdType id) : m_id{id} {};
  Entity(const Entity &) = default;
  Entity &operator=(const Entity &) = default;

  IdType getId() const { return m_id; }

  bool operator==(const Entity &e) const { return getId() == e.getId(); }
  bool operator!=(const Entity &e) const { return getId() != e.getId(); }
  bool operator<(const Entity &e) const { return getId() < e.getId(); }
  bool operator>(const Entity &e) const { return getId() > e.getId(); }

  template <typename T, typename... Args>
  void addComponent(Args &&...args);
  template <typename T>
  void removeComponent() const;
  template <typename T>
  bool hasComponent() const;
  template <typename T>
  T &getComponent() const;

 private:
  IdType m_id;
  EntityManager *entityManager = nullptr;
};

class EntityManager {
 public:
  EntityManager(World &world) : m_world{world} {};

 private:
  World &m_world;
};

template <typename T, typename... Args>
void Entity::addComponent(Args &&...args) {}

template <typename T>
void Entity::removeComponent() const {}

template <typename T>
bool Entity::hasComponent() const {}

template <typename T>
T &Entity::getComponent() const {}

#endif