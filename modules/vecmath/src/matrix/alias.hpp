#pragma once
#include "struct.hpp"

namespace Math {
    // generic
    template<typename T>
    using Mat2 = Mat<T, 2>;
    template<typename T>
    using Mat3 = Mat<T, 3>;
    template<typename T>
    using Mat4 = Mat<T, 4>;
    template<typename T>
    using Mat2x3 = Mat<T, 2, 3>;
    template<typename T>
    using Mat2x4 = Mat<T, 2, 4>;
    template<typename T>
    using Mat3x2 = Mat<T, 3, 2>;
    template<typename T>
    using Mat3x4 = Mat<T, 3, 4>;
    template<typename T>
    using Mat4x2 = Mat<T, 4, 2>;
    template<typename T>
    using Mat4x3 = Mat<T, 4, 3>;
    // float
    using Mat2F = Mat2<float>;
    using Mat3F = Mat3<float>;
    using Mat4F = Mat4<float>;
    using Mat2x3F = Mat2x3<float>;
    using Mat2x4F = Mat2x4<float>;
    using Mat3x2F = Mat3x2<float>;
    using Mat3x4F = Mat3x4<float>;
    using Mat4x2F = Mat4x2<float>;
    using Mat4x3F = Mat4x3<float>;
    // double
    using Mat2D = Mat2<double>;
    using Mat3D = Mat3<double>;
    using Mat4D = Mat4<double>;
    using Mat2x3D = Mat2x3<double>;
    using Mat2x4D = Mat2x4<double>;
    using Mat3x2D = Mat3x2<double>;
    using Mat3x4D = Mat3x4<double>;
    using Mat4x2D = Mat4x2<double>;
    using Mat4x3D = Mat4x3<double>;
    // int
    using Mat2I = Mat2<int>;
    using Mat3I = Mat3<int>;
    using Mat4I = Mat4<int>;
    using Mat2x3I = Mat2x3<int>;
    using Mat2x4I = Mat2x4<int>;
    using Mat3x2I = Mat3x2<int>;
    using Mat3x4I = Mat3x4<int>;
    using Mat4x2I = Mat4x2<int>;
    using Mat4x3I = Mat4x3<int>;
    // uint
    using Mat2U = Mat2<uint>;
    using Mat3U = Mat3<uint>;
    using Mat4U = Mat4<uint>;
    using Mat2x3U = Mat2x3<uint>;
    using Mat2x4U = Mat2x4<uint>;
    using Mat3x2U = Mat3x2<uint>;
    using Mat3x4U = Mat3x4<uint>;
    using Mat4x2U = Mat4x2<uint>;
    using Mat4x3U = Mat4x3<uint>;

    // vector alias
    // :: generic
    template<typename T, uint N>
    using Vec = Mat<T, N, 1>;
    template<typename T>
    using Vec2 = Vec<T, 2>;
    template<typename T>
    using Vec3 = Vec<T, 3>;
    template<typename T>
    using Vec4 = Vec<T, 4>;
    // :: float
    using Vec2F = Vec2<float>;
    using Vec3F = Vec3<float>;
    using Vec4F = Vec4<float>;
    // :: double
    using Vec2D = Vec2<double>;
    using Vec3D = Vec3<double>;
    using Vec4D = Vec4<double>;
    // :: int
    using Vec2I = Vec2<int32>;
    using Vec3I = Vec3<int32>;
    using Vec4I = Vec4<int32>;
    // :: uint
    using Vec2U = Vec2<uint32>;
    using Vec3U = Vec3<uint32>;
    using Vec4U = Vec4<uint32>;
}