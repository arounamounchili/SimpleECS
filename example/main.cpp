#include "../src/World.hpp"
#include <iostream>

using namespace SimpleECS;

struct TransformComponent
{
    int x, y; // Position
    TransformComponent(int x = 0, int y = 0)
    {
        this->x = x;
        this->y = y;
    }
};

struct MotionComponent
{
    float vx, vy; // velocity
    float ax, ay; // acceleration
    MotionComponent(float vx = 0, float vy = 0, float ax = 0.0, float ay = 0.0)
    {
        this->vx = vx;
        this->vy = vy;
        this->ax = ax;
        this->ay = ay;
    }
};

class MovementSystem : public System
{
public:
    MovementSystem()
    {
        requireComponent<TransformComponent>();
        requireComponent<MotionComponent>();
    }

    void Update()
    {
        for (auto entity : GetEntities())
        {
            auto &position = entity.GetComponent<TransformComponent>();
            auto &motion = entity.GetComponent<MotionComponent>();

            position.x += motion.vx;
            position.y += motion.vy;
            std::cout << "Position (x: " << position.x << " , y: " << position.y << ")" << std::endl;

            motion.vx += motion.ax;
            motion.vy += motion.ax;
            std::cout << "Velocity (vx: " << motion.vx << " , vy: " << motion.vy << ")" << std::endl;
        }
    }
};

int main()
{
    World world;
    auto entity = world.CreateEntity();
    entity.AddComponent<TransformComponent>(50, 50);
    entity.AddComponent<MotionComponent>(25, 25, 10, 10);
    world.GetSystemManager().AddSystem<MovementSystem>();

    for (int i = 0; i < 5; i++)
    {
        world.Update();
        world.GetSystemManager().GetSystem<MovementSystem>().Update();
    }
}