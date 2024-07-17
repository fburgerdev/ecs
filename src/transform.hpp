#pragma once
#include "vecmath/vecmath.hpp"

namespace ECS {
    // Transform
    struct Transform {
        // constructor
        Transform() = default;
        
        // position, rotation and scale
        Math::Vec3F position = Math::Vec3F(0);
        Math::Vec3F rotation = Math::Vec3F(0);
        Math::Vec3F scale = Math::Vec3F(1);
    };
}