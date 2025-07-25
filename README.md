# tiny\_ecs — A Minimalist Header-Only ECS for C++

**tiny\_ecs** is a simple, header-only Entity Component System (ECS) designed for educational use, and small projects. It's easy to integrate and requires no external dependencies.

---

## Features

* Header-only: just include and use.
* Parallelized execution with TBB
* Tuple-style component access via `getMultipleComponents`.
* `registerType`/`registerMultipleTypes` system for flexible component setup.
* Optional safety checks via `.hasValue()` or `unwrap()`.

---

## Installation

Just drop `tiny_ecs.h` into your project and include it:

```cpp
#define ECS_IMPLEMENTATION
#include "tiny_ecs.h"
```

---

## Example Usage

```cpp
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

    // Getting components manually
    auto refs = ECS::getMultipleComponents<Position, Velocity>(entity1);
    if(!refs) return;
    auto [pos, vel] = refs.unwrap();

    return 0;
}
```

---

## Key API Functions

| Function                                    | Description                                          |
| ------------------------------------------- | ---------------------------------------------------- |
| `ECS::registerType<T>()`                    | Register a single component type                     |
| `ECS::registerMultipleTypes<Ts...>()`       | Register multiple types at once                      |
| `ECS::newEntity()`                          | Create a new entity and return its ID                |
| `ECS::addComponent<T>(entity, component)`   | Add a component to an entity                         |
| `ECS::addMultipleComponents<Ts...>(...)`    | Add multiple components in one call                  |
| `ECS::getComponent<T>(entity)`              | Get a pointer-like wrapper for a single component    |
| `ECS::getMultipleComponents<Ts...>(entity)` | Get a tuple-like wrapper for multiple components     |
| `ECS::allEntitiesWith<Ts...>()`             | Iterate over all entities that have those components |
| `ECS::forEach<Ts...>(func, args)`           | Call func for all entities that have those components |
| `ECS::parallelForEach<Ts...>(func, args)`           | Call func for all entities that have those components |

---

## Dear ImGui Integration

`tiny_ecs_ui.h` offers a small integration into Dear ImGui for debugging and editing components

```cpp
#define ECS_IMPLEMENTATION
#include "tiny_ecs.h"
#include "tiny_ui.h"

struct Transform {
    Position pos;
    Velocity vel;
};

// your code ///
// Register components
ECS::registerType<Transform>();
ECS_UI::registerType<Transform>("Transform");
ECS_UI::addToType<Transform>("Position", offsetof(Transform, pos), ECS_UI::ELEMENT_TYPE::VEC2);
ECS_UI::addToType<Transform>("Velocity", offsetof(Transform, vel), ECS_UI::ELEMENT_TYPE::VEC2);

// your code ///
// ImGui Loop
ECS_UI::renderEntityList(entity_list_to_display, amount); 
OptionalEntityID selected = ECS_UI::currentEntity;
//ECS_UI::renderEntityInspector(ECS_UI::CHILD);
ECS_UI::renderEntityInspector(ECS_UI::OWN_WINDOW);
```



---

## Safety Notes

* `getComponent` and `getMultipleComponents` return optional-style wrappers.
* Use `.hasValue()` or `if (refs)` to check validity before unwrapping.
* Unwrapping invalid access is **undefined behavior**, just like `std::optional`.

---

## Why use this?

* Perfect for game jams, simulations, toy engines, or educational tools.
* No heavy architecture or boilerplate — start coding right away.
* Easy to extend or integrate into existing codebases.

---

## License

MIT License — free to use, modify, and distribute.
