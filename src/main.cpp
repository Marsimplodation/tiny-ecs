#define ECS_IMPLEMENTATION
#include "tiny_ecs.h"

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

    for(auto e : ECS::allEntitiesWith<Position, Velocitiy>()) {
        auto refs = ECS::getMultipleComponents<Position, Velocitiy>(e);
        //optionally check validity:
        //if(!refs) continue;
        auto [p, v] = refs.unwrap();

        //single component alternative:
        //auto ref = ECS::getComponent<Position>(e);
        //if(!ref) continue;
        //auto &p = ref.unwrap();
        p.x += v.x;
        p.y += v.y;
        printf("Entity %d: %f %f \n", e,p.x,p.y);
    }
    
    return 0;
}
