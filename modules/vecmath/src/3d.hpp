#pragma once
#include "matrix.hpp"

namespace Math {
    // translate
    template<floating_point T>
    auto TranslationMatrix(Vec3<T> translation) {
        return Mat4<T>({
            1, 0, 0, translation.x,
            0, 1, 0, translation.y,
            0, 0, 1, translation.z,
            0, 0, 0, 1
        });
    }
    // rotate
    template<floating_point T>
    auto RotationMatrix(Vec3<T> euler_rotation) {
        Mat3<T> mat;
        // sin / cos
        T sinx = sin(euler_rotation.x);
        T cosx = cos(euler_rotation.x);
        T siny = sin(euler_rotation.y);
        T cosy = cos(euler_rotation.y);
        T sinz = sin(euler_rotation.z);
        T cosz = cos(euler_rotation.z);
        // roll -> pitch -> yaw (ccw)
        mat.at(0, 0) = cosy * cosz + sinx * siny * sinz;
        mat.at(0, 1) = sinx * siny * cosz - cosy * sinz;
        mat.at(0, 2) = cosx * siny;
        mat.at(1, 0) = cosx * sinz;
        mat.at(1, 1) = cosx * cosz;
        mat.at(1, 2) = -sinx;
        mat.at(2, 0) = -siny * cosz + sinx * cosy * sinz;
        mat.at(2, 1) = sinx * cosy * cosz + siny * sinz;
        mat.at(2, 2) = cosx * cosy;
        return mat;
    }
    // scale
    template<floating_point T>
    auto ScaleMatrix(Vec3<T> scale) {
        return Mat3<T>({
            scale.x, 0, 0,
            0, scale.y, 0,
            0, 0, scale.z,
        });
    }

    // local space -> world space
    template<floating_point T>
    auto ModelMatrix(Vec3<T> position, Vec3<T> rotation, Vec3<T> scale) {
        auto out = Zero<T, 4>();
        out.insert(ScaleMatrix(scale) * RotationMatrix(rotation), { 0, 0 });
        out.insert(Vec4<T>(position, 1), { 0, 3 });
        return out;
    }
    // world space -> view space
    template<floating_point T>
    auto ViewMatrix(Vec3<T> position, Vec3<T> rotation) {
        Mat4<T> rotate = Identity<T, 4>();
        rotate.insert(transpose(RotationMatrix(rotation)), { 0, 0 });
        Mat4<T> translate = Identity<T, 4>();
        translate.insert(Vec4<T>(-position, 1), { 0, 3 });
        return rotate * translate;
    }
    // view space -> clip space (OPENGL specific)
    template<floating_point T>
    auto PerspectiveMatrix(T fov, T aspectRatio, T zNear, T zFar) {
        auto mat = Zero<T, 4>();
        // clip x, y
        mat.at(0, 0) = 1.0 / tan(fov / 2);
        mat.at(1, 1) = aspectRatio / tan(fov / 2); // (negation is OPENGL specific since y-axis is inverted)
        // clip z to [-1, 1] (OPENGL specific)
        mat.at(2, 2) = 2 * zFar / (zFar - zNear) - 1;
        mat.at(2, 3) = -2 * zNear * zFar / (zFar - zNear);
        mat.at(3, 2) = 1;
        return mat;
    }
}