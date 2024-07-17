#include "uuid.hpp"
#include <random>

namespace ECS {
    // generateUUID
    UUID generateUUID() {
        std::random_device device;
        std::mt19937_64 twister(device());
        std::uniform_int_distribution<std::mt19937_64::result_type> dist;
        return dist(twister);
    }
}