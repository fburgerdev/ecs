#pragma once
#include "common.hpp"
#include <concepts>

namespace ECS {
    // View
    template<typename T>
    concept View = requires(T x) {
        // { T() };
        { x.operator->() };
    };
}