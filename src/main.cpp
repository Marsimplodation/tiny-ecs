#include <chrono>
#include <cstdlib>
#define ECS_IMPLEMENTATION
#include "tiny_ecs.h"

struct Position {
    float x, y;
}; 

struct Velocity {
    float x, y;
}; 

struct Timer {
    Timer(const char* name) : name(name), start(std::chrono::high_resolution_clock::now()) {
        printf("Timer '%s' started.\n", name);
    }
    ~Timer() {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(end - start).count();
        printf("Timer '%s' ended. Duration: %.3f ms.\n", name, duration);
    }
    const char *name;
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
};




void movementSystem(EntityID entity, Position & p, Velocity & v, float f) {
    p.x += v.x * f;
    p.y += v.y * f;
}

int main (int argc, char *argv[]) {
    ECS::registerMultipleTypes<Position, Velocity>();
    const int count = 500000;

    #define rnd(s) ((float)std::rand()/(float)RAND_MAX) * s
    for(int i = 0; i<count; ++i)
        ECS::addMultipleComponents(ECS::newEntity(), Position{rnd(5),rnd(5)}, Velocity{rnd(1), rnd(1)});


    {
        Timer t("component retrieval and update simple");
        float f = 1.0f/60.0f;
        for(int i = 0; i < count; ++i) {
            auto refs = ECS::getMultipleComponents<Position, Velocity>(i);
            if(!refs) continue;
            auto [p, v] = refs.unwrap();
                p.x += v.x * f;
                p.y += v.y * f;
        }
    }
    {
        Timer t("component retrieval and update function");
        ECS::for_each<Position, Velocity>(movementSystem, 1.0f/60.0f);
    }
    {
        Timer t("component retrieval and update lambda");
        ECS::for_each<Position, Velocity>(
            [](EntityID entity, Position & p, Velocity & v, float f) {
                p.x += v.x * f;
                p.y += v.y * f;
            },
            1.0f/60.0f);
    }
    return 0;
}
