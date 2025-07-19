# tiny\_ecs — A Minimalist Header-Only ECS for C++

**tiny\_ecs** is a simple, header-only Entity Component System (ECS) designed for educational use, and small projects. It's easy to integrate and requires no external dependencies.

---

## Features

* Header-only: just include and use.
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

typedef struct {
    float x, y;
} Position, Velocitiy;

int main (int argc, char *argv[]) {
    // Register components
    ECS::registerMultipleTypes<Position, Velocitiy>();

    // Create entities and attach components
    EntityID entitiy1 = ECS::newEntity();
    ECS::addMultipleComponents(entitiy1, Position{1,2}, Velocitiy{0.1, 0.05});

    EntityID entitiy2 = ECS::newEntity();
    ECS::addComponent(entitiy2, Position{2,2});
    ECS::addComponent(entitiy2, Velocitiy{2,2});

    // Simulate a movement system
    for(auto e : ECS::allEntitiesWith<Position, Velocitiy>()) {
        auto refs = ECS::getMultipleComponents<Position, Velocitiy>(e);

        // Optionally check for presence:
        // if (!refs) continue;

        auto [p, v] = refs.unwrap();

        // Alternative: single component access
        // auto ref = ECS::getComponent<Position>(e);
        // if (!ref) continue;
        // auto& p = ref.unwrap();

        p.x += v.x;
        p.y += v.y;

        printf("Entity %d: %f %f\n", e, p.x, p.y);
    }

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

## Planned features

* Ability to register systems with parallel execution to get the S of ECS

---

## License

MIT License — free to use, modify, and distribute.
