#pragma once
#include "uuid.hpp"
#include "view.hpp"

namespace ECS {
    // SceneMemory
    template<typename T>
    concept SceneMemory = requires(T x, UUID uuid) {
        // general
        { T() };
        // entity
        // { x.createEntity() };
        // { x.destroyEntity(uuid) };
        // { x.getEntity(uuid) };
        // { x.hasEntity(uuid) };
        // components
        // { x.createComponent() };
        // { x.destroyComponent(uuid) };
        // { x.getComponent(uuid) };
        // { x.hasComponent(uuid) };
    };
}