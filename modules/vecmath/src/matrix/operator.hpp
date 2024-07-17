#pragma once
#include "struct.hpp"

namespace Math {
    // operator- (negate)
    template<typename T, uint N, uint M>
    auto operator-(const Mat<T, N, M>& mat) {
        Mat<T, N, M> out;
        for (uint i = 0; i < N * M; ++i) {
            out.at(i) = -mat.at(i);
        }
        return out;
    }
    // operator+= (add)
    template<typename T, uint N, uint M>
    auto& operator+=(Mat<T, N, M>& mat, const Mat<T, N, M>& other) {
        for (uint i = 0; i < N * M; ++i) {
            mat.at(i) += other.at(i);
        }
        return mat;
    }
    // operator-= (subtract)
    template<typename T, uint N, uint M>
    auto& operator-=(Mat<T, N, M>& mat, const Mat<T, N, M>& other) {
        for (uint i = 0; i < N * M; ++i) {
            mat.at(i) -= other.at(i);
        }
        return mat;
    }
    // operator*= (multiply scalar)
    template<typename T, uint N, uint M>
    auto& operator*=(Mat<T, N, M>& mat, auto scalar) {
        for (uint i = 0; i < N * M; ++i) {
            mat.at(i) *= scalar;
        }
        return mat;
    }
    // operator/= (divide scalar)
    template<typename T, uint N, uint M>
    auto& operator/=(Mat<T, N, M>& mat, auto scalar) {
        for (uint i = 0; i < N * M; ++i) {
            mat.at(i) /= scalar;
        }
        return mat;
    }
    // operator+ (sum)
    template<typename T, uint N, uint M>
    auto operator+(const Mat<T, N, M>& mat1, const Mat<T, N, M>& mat2) {
        Mat<T, N, M> out(mat1);
        out += mat2;
        return out;
    }
    // operator- (difference)
    template<typename T, uint N, uint M>
    auto operator-(const Mat<T, N, M>& mat1, const Mat<T, N, M>& mat2) {
        Mat<T, N, M> out(mat1);
        out -= mat2;
        return out;
    }
    // operator* (product scalar)
    template<typename T, uint N, uint M>
    auto operator*(const Mat<T, N, M>& mat, auto scalar) {
        Mat<T, N, M> out(mat);
        out *= scalar;
        return out;
    }
    // operator/ (quotient scalar)
    template<typename T, uint N, uint M>
    auto operator/(const Mat<T, N, M>& mat, auto scalar) {
        Mat<T, N, M> out(mat);
        out /= scalar;
        return out;
    }
    
    // operator* (product matrix)
    template<typename T, uint N, uint M, uint L>
    auto operator*(const Mat<T, N, M>& mat1, const Mat<T, M, L>& mat2) {
        auto out = Zero<T, N, L>();
        for (uint n = 0; n < N; ++n) {
            for (uint l = 0; l < L; ++l) {
                for (uint m = 0; m < M; ++m) {
                    out.at(n, l) += mat1.at(n, m) * mat2.at(m, l);
                }
            }
        }
        return out;
    }
    // operator*= (multiply matrix)
    template<typename T, uint N>
    auto& operator*=(Mat<T, N>& mat1, const Mat<T, N>& mat2) {
        mat1 = mat1 * mat2;
        return mat1;
    }
}