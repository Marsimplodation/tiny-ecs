#define ECS_IMPLEMENTATION
#include "tiny_ecs.h"

struct Width{float w;};
struct Height{float h;};
struct Radius{float r;};
struct Area{float a;};

typedef struct {
    float x, y;
}  Position, Velocitiy;



int main (int argc, char *argv[]) {
    ECS::registerMultipleTypes<Position, Velocitiy>();

    EntityID entitiy1 = ECS::newEntity();
    ECS::addMultipleComponents(entitiy1, Position{1,2}, Velocitiy{0.1, 0.05});
    EntityID entitiy2 = ECS::newEntity();
    ECS::addComponent(entitiy2, Position{2,2});
    ECS::addComponent(entitiy2, Velocitiy{2,2});

    //systems
    for(auto e : ECS::allEntitiesWith<Position, Velocitiy>()) {
        auto [p, v] = ECS::getMultipleComponents<Position, Velocitiy>(e).unwrap();
        p.x += v.x;
        p.y += v.y;
    }
    
    return 0;
}
