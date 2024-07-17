#include "vecmath.hpp"

int main() {
    std::cout << std::is_trivial_v<Math::Vec3F> << std::endl;
    Math::Vec3F vec = Math::normalize(Math::Vec3F(1, 2, 3));
    
    Math::Mat3F mat = Math::Identity<float, 3>();
    mat.at(0, 1) = 2;
    
    std::cout << Math::transpose(mat * vec) << std::endl;
    return EXIT_SUCCESS;
}