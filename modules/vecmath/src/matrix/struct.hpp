#pragma once
#include "arithmetic.hpp"

namespace Math {
    // Mat
    template<typename T, uint N, uint M = N>
    class Mat {
    public:
        // constructor
        Mat() = default;
        Mat(T (&values)[N * M]) {
            for (uint i = 0; i < N * M; ++i) {
                m_Data[i] = values[i];
            }
        }
        Mat(T (&&values)[N * M]) {
            for (uint i = 0; i < N * M; ++i) {
                m_Data[i] = values[i];
            }
        }
        Mat(T (&values)[N][M]) {
            for (uint n = 0; n < N; ++n) {
                for (uint m = 0; m < M; ++m) {
                    m_Data[M * n + m] = values[n][m];
                }
            }
        }
        Mat(T (&&values)[N][M]) {
            for (uint n = 0; n < N; ++n) {
                for (uint m = 0; m < M; ++m) {
                    m_Data[M * n + m] = values[n][m];
                }
            }
        }
        template<typename U>
        Mat(const Mat<U, N, M>& mat) {
            for (uint i = 0; i < N * M; ++i) {
                m_Data[i] = (T)mat.at(i);
            }
        }
        // access
        // :: at
        T& at(uint index) {
            ASSERT(inRange(index, 0, N * M))
            return m_Data[index];
        }
        const T& at(uint index) const {
            ASSERT(inRange(index, 0, N * M))
            return m_Data[index];
        }
        T& at(uint n, uint m) {
            ASSERT(inRange(n, 0, N) && inRange(m, 0, M))
            return m_Data[M * n + m];
        }
        const T& at(uint n, uint m) const {
            ASSERT(inRange(n, 0, N) && inRange(m, 0, M))
            return m_Data[M * n + m];
        }
        // :: operator[]
        T& operator[](uint index) {
            return at(index);
        }
        const T& operator[](uint index) const {
            return at(index);
        }
        // insert
        template<typename U, uint N2, uint M2>
        auto insert(const Mat<U, N2, M2>& value, const Mat<uint, 2, 1>& where);
    private:
        // data
        T m_Data[N * M];
    };
    // Mat 2 x 1
    template<typename T>
    class Mat<T, 2, 1> {
    public:
        // constructor
        Mat() = default;
        Mat(T value)
            : Mat(value, value) {}
        Mat(T x, T y)
            : x(x), y(y) {}
        template<typename U>
        Mat(const Mat<U, 2, 1>& vec)
            : Mat(static_cast<T>(vec.x), static_cast<T>(vec.y)) {}
        // access
        // :: at
        T& at(uint index) {
            ASSERT(inRange(index, 0, 1))
            return index == 0 ? x : y;
        }
        const T& at(uint index) const {
            ASSERT(inRange(index, 0, 1))
            return index == 0 ? x : y;
        }
        T& at(uint n, uint m) {
            ASSERT(inRange(n, 0, 1) && m == 0)
            return at(n);
        }
        const T& at(uint n, uint m) const {
            ASSERT(inRange(n, 0, 1) && m == 0)
            return at(n);
        }
        // :: operator[]
        T& operator[](uint index) {
            return at(index);
        }
        const T& operator[](uint index) const {
            return at(index);
        }
        // insert
        template<typename U, uint N2, uint M2>
        auto insert(const Mat<U, N2, M2>& value, const Mat<uint, 2, 1>& where);
        // values
        T x, y;
    };
    // Mat 3 x 1
    template<typename T>
    class Mat<T, 3, 1> {
    public:
        // constructor
        Mat() = default;
        Mat(T value)
            : Mat(value, value, value) {}
        Mat(T x, T y, T z)
            : x(x), y(y), z(z) {}
        Mat(const Mat<T, 2, 1>& xy, T z)
            : Mat(xy.x, xy.y, z) {}
        Mat(T x, const Mat<T, 2, 1>& yz)
            : Mat(x, yz.x, yz.y) {}
        template<typename U>
        Mat(const Mat<U, 3, 1>& vec)
            : Mat(static_cast<T>(vec.x), static_cast<T>(vec.y), static_cast<T>(vec.z)) {}
        // access
        // :: at
        T& at(uint index) {
            ASSERT(inRange(index, 0, 2))
            return index == 0 ? x : (index == 1 ? y : z);
        }
        const T& at(uint index) const {
            ASSERT(inRange(index, 0, 2))
            return index == 0 ? x : (index == 1 ? y : z);
        }
        T& at(uint n, uint m) {
            ASSERT(inRange(n, 0, 2) && m == 0)
            return at(n);
        }
        const T& at(uint n, uint m) const {
            ASSERT(inRange(n, 0, 2) && m == 0)
            return at(n);
        }
        // :: operator[]
        T& operator[](uint index) {
            return at(index);
        }
        const T& operator[](uint index) const {
            return at(index);
        }
        // insert
        template<typename U, uint N2, uint M2>
        auto insert(const Mat<U, N2, M2>& value, const Mat<uint, 2, 1>& where);
        // values
        T x, y, z;
    };
    // Mat 4 x 1
    template<typename T>
    class Mat<T, 4, 1> {
    public:
        // constructor
        Mat() = default;
        Mat(T value)
            : Mat(value, value, value, value) {}
        Mat(T x, T y, T z, T w)
            : x(x), y(y), z(z), w(w) {}
        Mat(const Mat<T, 2, 1>& xy, T z, T w)
            : Mat(xy.x, xy.y, z, w) {}
        Mat(T x, const Mat<T, 2, 1>& yz, T w)
            : Mat(x, yz.x, yz.y, w) {}
        Mat(T x, T y, const Mat<T, 2, 1>& zw)
            : Mat(x, y, zw.x, zw.y) {}
        Mat(const Mat<T, 2, 1>& xy, const Mat<T, 2, 1>& yz)
            : Mat(xy.x, xy.y, yz.x, yz.y) {}
        Mat(const Mat<T, 3, 1>& xyz, T w)
            : Mat(xyz.x, xyz.y, xyz.z, w) {}
        Mat(T x, const Mat<T, 3, 1>& yzw)
            : Mat(x, yzw.x, yzw.y, yzw.z) {}
        template<typename U>
        Mat(const Mat<U, 4, 1>& vec)
            : Mat(static_cast<T>(vec.x), static_cast<T>(vec.y), static_cast<T>(vec.z), static_cast<T>(vec.w)) {}
        // access
        // :: at
        T& at(uint index) {
            ASSERT(inRange(index, 0, 3))
            return index == 0 ? x : (index == 1 ? y : (index == 2 ? z : w));
        }
        const T& at(uint index) const {
            ASSERT(inRange(index, 0, 3))
            return index == 0 ? x : (index == 1 ? y : (index == 2 ? z : w));
        }
        T& at(uint n, uint m) {
            ASSERT(inRange(n, 0, 3) && m == 0)
            return at(n);
        }
        const T& at(uint n, uint m) const {
            ASSERT(inRange(n, 0, 3) && m == 0)
            return at(n);
        }
        // :: operator[]
        T& operator[](uint index) {
            return at(index);
        }
        const T& operator[](uint index) const {
            return at(index);
        }
        // insert
        template<typename U, uint N2, uint M2>
        auto insert(const Mat<U, N2, M2>& value, const Mat<uint, 2, 1>& where);
        // values
        T x, y, z, w;
    };
}