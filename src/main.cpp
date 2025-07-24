#define ECS_IMPLEMENTATION
#include "tiny_ecs.h"

struct Position {
    float x, y;
};
struct Velocity {
    float x, y;
};

void movementSystem(EntityID e, Position & p, Velocity & v) {
    p.x += v.x;
    p.y += v.y;
    printf("Entity %d: %f %f\n", e, p.x, p.y);
}

int main (int argc, char *argv[]) {
    // Register components
    ECS::registerMultipleTypes<Position, Velocity>();

    // Create entities and attach components
    EntityID entitiy1 = ECS::newEntity();
    ECS::addMultipleComponents(entitiy1, Position{1,2}, Velocity{0.1, 0.05});

    EntityID entitiy2 = ECS::newEntity();
    ECS::addComponent(entitiy2, Position{2,2});
    ECS::addComponent(entitiy2, Velocity{2,2});

    // Simulate a movement system
    ECS::forEach<Position, Velocity>(movementSystem);
    ECS::parallelForEach<Position, Velocity>(movementSystem);

    return 0;
}
