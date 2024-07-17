#pragma once
// #include "common.hpp" (HPPMERGE)
#include <ranges> 
#include <memory> 
#include <string> 
#include <string_view> 
#include <array> 
#include <vector> 
#include <stack> 
#include <queue> 
#include <deque> 
#include <unordered_set> 
#include <map> 
#include <set> 
#include <unordered_map> 
#include <functional> 
#include <optional> 
#include <iostream> 
namespace Math {
    namespace stdr = std::ranges;
    using address = std::size_t;
    using int8 = std::int8_t;
    using int16 = std::int16_t;
    using int32 = std::int32_t;
    using int64 = std::int64_t;
    using uint8 = std::uint8_t;
    using uint16 = std::uint16_t;
    using uint32 = std::uint32_t;
    using uint64 = std::uint64_t;
    using string = std::string;
    using string_view = std::string_view;
    template<typename T, address N>
    using Array = std::array<T, N>;
    template<typename T>
    using List = std::vector<T>;
    template<typename T>
    using Stack = std::stack<T>;
    template<typename T>
    using Queue = std::queue<T>;
    template<typename T>
    using Deque = std::deque<T>;
    template<typename T>
    using Set = std::set<T>;
    template<typename Key, typename Value>
    using Map = std::map<Key, Value>;
    template<typename T>
    using HashSet = std::unordered_set<T>;
    template<typename Key, typename Value>
    using HashMap = std::unordered_map<Key, Value>;
    using std::forward;
    using std::move;
    using std::make_unique;
    using std::make_shared;
    using std::unique_ptr;
    using std::shared_ptr;
    using std::weak_ptr;
    using std::function;
    template<typename T>
    using Opt = std::optional<T>;
    using std::cout;
    using std::endl;
}
// #include "constants.hpp" (HPPMERGE)
namespace Math {
    inline constexpr double PI = 3.141592653589793238462643383279;
    inline constexpr double PI_HALFS = PI / 2.0;
    inline constexpr double TAU = 2.0 * PI;
    inline constexpr double DEG_0 = 0.0;
    inline constexpr double DEG_90 = PI / 2.0;
    inline constexpr double DEG_180 = PI / 2.0;
    inline constexpr double DEG_270 = 5.0 * PI / 4.0;
    inline constexpr double DEG_360 = 2.0 * PI;
    inline constexpr double EULER = 2.718281828459045235360287471352;
    inline constexpr double EULER_HALFS = EULER / 2;
    inline constexpr double GOLDEN_RATIO = 1.618033988749894848204586834365;
}
// #include "logging.hpp" (HPPMERGE)
#if defined(BEAVER_LOGGING)
#include "beaver/beaver.hpp"
#else
#define LOG_TRACE(...)
#define LOG_DEBUG(...)
#define LOG_INFO(...)
#define LOG_WARN(...)
#define LOG_ERROR(...)
#define LOG_FATAL(...)
#define ASSERT(...)
#define ASSERT_MSG(...)
#endif
// #include "arithmetic.hpp" (HPPMERGE)
#include <concepts> 
#include <cmath> 
namespace Math {
    using std::integral;
    using std::floating_point;
    template <typename T>
    concept numeric = integral<T> || floating_point<T>;
    template<numeric T>
    T abs(T x) {
        return x > 0 ? x : -x;
    }
    template<floating_point T>
    T floor(T x) {
        return std::floor(x);
    }
    template<floating_point T>
    T ceil(T x) {
        return std::ceil(x);
    }
    template<floating_point T>
    T sqrt(T x) {
        ASSERT(x > 0)
        return std::sqrt(x);
    }
    template<floating_point T>
    T sin(T x) {
        return std::sin(x);
    }
    template<floating_point T>
    T cos(T x) {
        return std::cos(x);
    }
    template<floating_point T>
    T tan(T x) {
        ASSERT((x / PI_HALFS) != floor(x / PI_HALFS))
        return std::tan(x);
    }
    template<floating_point T>
    T asin(T x) {
        ASSERT(abs(x) <= 1)
        return std::asin(x);
    }
    template<floating_point T>
    T acos(T x) {
        ASSERT(abs(x) <= 1)
        return std::acos(x);
    }
    template<floating_point T>
    T atan(T x) {
        return std::atan(x);
    }
    template<floating_point T>
    T exp(T x) {
        return std::exp(x);
    }
    template<floating_point T>
    T ln(T x) {
        ASSERT(x > 0)
        return std::log(x);
    }
    template<floating_point T>
    T log2(T x) {
        ASSERT(x > 0)
        return std::log2(x);
    }
    template<floating_point T>
    T log10(T x) {
        ASSERT(x > 0)
        return std::log10(x);
    }
    template<floating_point T>
    T pow(T base, T exponent) {
        ASSERT(base > 0)
        return std::pow(base, exponent);
    }
    template<numeric T>
    T pow2(T x) {
        return x * x;
    }
    template<numeric T>
    T pow3(T x) {
        return x * x * x;
    }
    template<numeric T>
    T pow4(T x) {
        return x * x * x * x;
    }
    template<numeric T1, numeric T2, numeric... TRest>
    auto max(const T1& val1, const T2& val2, TRest&&... rest) {
        if constexpr(sizeof...(TRest) == 0) {
            return val1 >= val2 ? val1 : val2;
        }
        else {
            return max(val1 >= val2 ? val1 : val2, forward<TRest>(rest)...);
        }
    }
    template<numeric T1, numeric T2, numeric... TRest>
    auto min(const T1& val1, const T2& val2, TRest&&... rest) {
        if constexpr(sizeof...(TRest) == 0) {
            return val1 > val2 ? val2 : val1;
        }
        else {
            return min(val1 > val2 ? val2 : val1, forward<TRest>(rest)...);
        }
    }
    template<numeric T>
    T clamp(T x, auto minValue, auto maxValue) {
        return max(minValue, min(x, maxValue));
    }
    template<numeric T>
    T clamp01(T x) {
        return clamp(x, 0, 1);
    }
    template<numeric T>
    bool inRange(T x, auto minValue, auto maxValue) {
        return x >= minValue && x <= maxValue;
    }
    template<numeric T>
    bool inRange01(T x) {
        return inRange(x, 0, 1);
    }
}
// #include "struct.hpp" (HPPMERGE)
namespace Math {
    template<typename T, uint N, uint M = N>
    class Mat {
    public:
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
        T& operator[](uint index) {
            return at(index);
        }
        const T& operator[](uint index) const {
            return at(index);
        }
        template<typename U, uint N2, uint M2>
        auto insert(const Mat<U, N2, M2>& value, const Mat<uint, 2, 1>& where);
    private:
        T m_Data[N * M];
    };
    template<typename T>
    class Mat<T, 2, 1> {
    public:
        Mat() = default;
        Mat(T value)
            : Mat(value, value) {}
        Mat(T x, T y)
            : x(x), y(y) {}
        template<typename U>
        Mat(const Mat<U, 2, 1>& vec)
            : Mat(static_cast<T>(vec.x), static_cast<T>(vec.y)) {}
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
        T& operator[](uint index) {
            return at(index);
        }
        const T& operator[](uint index) const {
            return at(index);
        }
        template<typename U, uint N2, uint M2>
        auto insert(const Mat<U, N2, M2>& value, const Mat<uint, 2, 1>& where);
        T x, y;
    };
    template<typename T>
    class Mat<T, 3, 1> {
    public:
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
        T& operator[](uint index) {
            return at(index);
        }
        const T& operator[](uint index) const {
            return at(index);
        }
        template<typename U, uint N2, uint M2>
        auto insert(const Mat<U, N2, M2>& value, const Mat<uint, 2, 1>& where);
        T x, y, z;
    };
    template<typename T>
    class Mat<T, 4, 1> {
    public:
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
        T& operator[](uint index) {
            return at(index);
        }
        const T& operator[](uint index) const {
            return at(index);
        }
        template<typename U, uint N2, uint M2>
        auto insert(const Mat<U, N2, M2>& value, const Mat<uint, 2, 1>& where);
        T x, y, z, w;
    };
}
// #include "construct.hpp" (HPPMERGE)
namespace Math {
    template<typename T, uint N, uint M = N>
    auto Zero() {
        Mat<T, N, M> mat;
        for (uint row = 0; row < N; ++row) {
            for (uint col = 0; col < M; ++col) {
                mat.at(row, col) = T(0);
            }
        }
        return mat;
    }
    template<typename T, uint N>
    auto Identity() {
        auto mat = Zero<T, N>();
        for (uint n = 0; n < N; ++n) {
            mat.at(n, n) = T(1);
        }
        return mat;
    }
    template<typename T, uint N, uint M>
    template<typename U, uint N2, uint M2>
    auto Mat<T, N, M>::insert(const Mat<U, N2, M2>& value, const Mat<uint, 2, 1>& where) {
        ASSERT(N2 + where.x <= N && M2 + where.y <= M)
        for (uint n = 0; n < N2; ++n) {
            for (uint m = 0; m < M2; ++m) {
                at(where.x + n, where.y + m) = T(value.at(n, m));
            }
        }
        return *this;
    }
    template<typename T>
    template<typename U, uint N2, uint M2>
    auto Mat<T, 2, 1>::insert(const Mat<U, N2, M2>& value, const Mat<uint, 2, 1>& where) {
        ASSERT(N2 + where.x <= 2 && M2 + where.y <= 1)
        for (uint n = 0; n < N2; ++n) {
            for (uint m = 0; m < M2; ++m) {
                at(where.x + n, where.y + m) = T(value.at(n, m));
            }
        }
        return *this;
    }
    template<typename T>
    template<typename U, uint N2, uint M2>
    auto Mat<T, 3, 1>::insert(const Mat<U, N2, M2>& value, const Mat<uint, 2, 1>& where) {
        ASSERT(N2 + where.x <= 3 && M2 + where.y <= 1)
        for (uint n = 0; n < N2; ++n) {
            for (uint m = 0; m < M2; ++m) {
                at(where.x + n, where.y + m) = T(value.at(n, m));
            }
        }
        return *this;
    }
    template<typename T>
    template<typename U, uint N2, uint M2>
    auto Mat<T, 4, 1>::insert(const Mat<U, N2, M2>& value, const Mat<uint, 2, 1>& where) {
        ASSERT(N2 + where.x <= 4 && M2 + where.y <= 1)
        for (uint n = 0; n < N2; ++n) {
            for (uint m = 0; m < M2; ++m) {
                at(where.y + n, where.x + m) = T(value.at(n, m));
            }
        }
        return *this;
    }
    template<uint N2, uint M2, typename T, uint N, uint M>
    auto resize(const Mat<T, N, M>& mat) {
        Mat<T, N2, M2> out;
        out.insert(mat, { 0, 0 });
        return out;
    }
}
// #include "operator.hpp" (HPPMERGE)
namespace Math {
    template<typename T, uint N, uint M>
    auto operator-(const Mat<T, N, M>& mat) {
        Mat<T, N, M> out;
        for (uint i = 0; i < N * M; ++i) {
            out.at(i) = -mat.at(i);
        }
        return out;
    }
    template<typename T, uint N, uint M>
    auto& operator+=(Mat<T, N, M>& mat, const Mat<T, N, M>& other) {
        for (uint i = 0; i < N * M; ++i) {
            mat.at(i) += other.at(i);
        }
        return mat;
    }
    template<typename T, uint N, uint M>
    auto& operator-=(Mat<T, N, M>& mat, const Mat<T, N, M>& other) {
        for (uint i = 0; i < N * M; ++i) {
            mat.at(i) -= other.at(i);
        }
        return mat;
    }
    template<typename T, uint N, uint M>
    auto& operator*=(Mat<T, N, M>& mat, auto scalar) {
        for (uint i = 0; i < N * M; ++i) {
            mat.at(i) *= scalar;
        }
        return mat;
    }
    template<typename T, uint N, uint M>
    auto& operator/=(Mat<T, N, M>& mat, auto scalar) {
        for (uint i = 0; i < N * M; ++i) {
            mat.at(i) /= scalar;
        }
        return mat;
    }
    template<typename T, uint N, uint M>
    auto operator+(const Mat<T, N, M>& mat1, const Mat<T, N, M>& mat2) {
        Mat<T, N, M> out(mat1);
        out += mat2;
        return out;
    }
    template<typename T, uint N, uint M>
    auto operator-(const Mat<T, N, M>& mat1, const Mat<T, N, M>& mat2) {
        Mat<T, N, M> out(mat1);
        out -= mat2;
        return out;
    }
    template<typename T, uint N, uint M>
    auto operator*(const Mat<T, N, M>& mat, auto scalar) {
        Mat<T, N, M> out(mat);
        out *= scalar;
        return out;
    }
    template<typename T, uint N, uint M>
    auto operator/(const Mat<T, N, M>& mat, auto scalar) {
        Mat<T, N, M> out(mat);
        out /= scalar;
        return out;
    }
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
    template<typename T, uint N>
    auto& operator*=(Mat<T, N>& mat1, const Mat<T, N>& mat2) {
        mat1 = mat1 * mat2;
        return mat1;
    }
}
// #include "alias.hpp" (HPPMERGE)
namespace Math {
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
    using Mat2F = Mat2<float>;
    using Mat3F = Mat3<float>;
    using Mat4F = Mat4<float>;
    using Mat2x3F = Mat2x3<float>;
    using Mat2x4F = Mat2x4<float>;
    using Mat3x2F = Mat3x2<float>;
    using Mat3x4F = Mat3x4<float>;
    using Mat4x2F = Mat4x2<float>;
    using Mat4x3F = Mat4x3<float>;
    using Mat2D = Mat2<double>;
    using Mat3D = Mat3<double>;
    using Mat4D = Mat4<double>;
    using Mat2x3D = Mat2x3<double>;
    using Mat2x4D = Mat2x4<double>;
    using Mat3x2D = Mat3x2<double>;
    using Mat3x4D = Mat3x4<double>;
    using Mat4x2D = Mat4x2<double>;
    using Mat4x3D = Mat4x3<double>;
    using Mat2I = Mat2<int>;
    using Mat3I = Mat3<int>;
    using Mat4I = Mat4<int>;
    using Mat2x3I = Mat2x3<int>;
    using Mat2x4I = Mat2x4<int>;
    using Mat3x2I = Mat3x2<int>;
    using Mat3x4I = Mat3x4<int>;
    using Mat4x2I = Mat4x2<int>;
    using Mat4x3I = Mat4x3<int>;
    using Mat2U = Mat2<uint>;
    using Mat3U = Mat3<uint>;
    using Mat4U = Mat4<uint>;
    using Mat2x3U = Mat2x3<uint>;
    using Mat2x4U = Mat2x4<uint>;
    using Mat3x2U = Mat3x2<uint>;
    using Mat3x4U = Mat3x4<uint>;
    using Mat4x2U = Mat4x2<uint>;
    using Mat4x3U = Mat4x3<uint>;
    template<typename T, uint N>
    using Vec = Mat<T, N, 1>;
    template<typename T>
    using Vec2 = Vec<T, 2>;
    template<typename T>
    using Vec3 = Vec<T, 3>;
    template<typename T>
    using Vec4 = Vec<T, 4>;
    using Vec2F = Vec2<float>;
    using Vec3F = Vec3<float>;
    using Vec4F = Vec4<float>;
    using Vec2D = Vec2<double>;
    using Vec3D = Vec3<double>;
    using Vec4D = Vec4<double>;
    using Vec2I = Vec2<int32>;
    using Vec3I = Vec3<int32>;
    using Vec4I = Vec4<int32>;
    using Vec2U = Vec2<uint32>;
    using Vec3U = Vec3<uint32>;
    using Vec4U = Vec4<uint32>;
}
// #include "norm.hpp" (HPPMERGE)
namespace Math {
    template<typename T, uint N, uint M>
    auto inner(const Mat<T, N, M>& mat1, const Mat<T, N, M>& mat2) {
        T out = 0;
        for (uint i = 0; i < N * M; ++i) {
            out += mat1.at(i) * mat2.at(i);
        }
        return out;
    }
    template<typename T, uint N, uint M>
    auto inner(const Mat<T, N, M>& mat) {
        return inner(mat, mat);
    }
    template<typename T, uint N, uint M>
    auto transpose(const Mat<T, N, M>& mat) {
        Mat<T, M, N> out;
        for (uint n = 0; n < N; ++n) {
            for (uint m = 0; m < M; ++m) {
                out.at(m, n) = mat.at(n, m);
            }
        }
        return out;
    }
    template<floating_point T, uint N, uint M>
    auto norm(const Mat<T, N, M>& mat) {
        return sqrt(inner(mat));
    }
    template<floating_point T, uint N, uint M>
    auto normalize(const Mat<T, N, M>& mat) {
        return mat / norm(mat);
    }
    template<typename T, uint N>
    auto dot(const Vec<T, N>& v1, const Vec<T, N>& v2) {
        T out = 0;
        for (uint n = 0; n < N; ++n) {
            out += v1.at(n) * v2.at(n);
        }
        return out;
    }
    template<typename T, uint N>
    auto dot(const Vec<T, N>& v) {
        return dot(v, v);
    }
    template<typename T>
    auto cross(const Vec3<T>& v1, const Vec3<T>& v2) {
        return Vec3<T>(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
    }
    template<floating_point T, uint N>
    auto length(const Vec<T, N>& v) {
        return sqrt(dot(v));
    }
    template<floating_point T, uint N>
    auto distance(const Vec<T, N>& v1, const Vec<T, N>& v2) {
        return length(v2 - v1);
    }
}
// #include "ostream.hpp" (HPPMERGE)
namespace Math {
    template <typename T, uint N, uint M>
    std::ostream& operator<<(std::ostream& os, const Mat<T, N, M>& mat) {
        string lines[N];
        string numbers[N];
        for (uint j = 0; j < M; ++j) {
            for (uint i = 0; i < N; ++i) {
                numbers[i] = std::to_string(mat.at(i, j));
            }
            uint max = 0;
            for (uint i = 0; i < N; ++i) {
                max = max < numbers[i].size() ? numbers[i].size() : max;
            }
            for (uint i = 0; i < N; ++i) {
                lines[i].push_back('|');
                for (uint j = 0; j < (max - numbers[i].size() + 1) / 2; ++j) {
                    lines[i].push_back(' ');
                }
                lines[i] += numbers[i];
                for (uint j = 0; j < (max - numbers[i].size()) / 2; ++j) {
                    lines[i].push_back(' ');
                }
            }
        }
        os << '\n';
        for (uint i = 0; i < N; ++i) {
            os << lines[i] << '|' << '\n';
        }
        return os;
    }
}
// #include "curves.hpp" (HPPMERGE)
namespace Math {
    template<floating_point T, uint N>
    auto lerp(const Vec<T, N>& v1, const Vec<T, N>& v2, T t) {
        ASSERT(inRange01(t))
        return v1 * t + v2 * (1 - t);
    }
    template<floating_point T, uint N>
    auto quadratic(const Vec<T, N>& v1, const Vec<T, N>& v2, const Vec<T, N>& v3, T t) {
        ASSERT(inRange01(t))
        return v1 * pow2(1 - t) + v1 * (2 * (1 - t)) + v3 * pow2(t);
    }
    template<floating_point T, uint N>
    auto cubic(const Vec<T, N>& v1, const Vec<T, N>& v2, const Vec<T, N>& v3, const Vec<T, N>& v4, T t) {
        ASSERT(inRange01(t))
        return v1 * pow3(1 - t) + v1 * (3 * pow2(1 - t) * t) + v1 * (3 * (1 - t) * pow(t)) + v3 * pow3(t);
    }
}
// #include "3d.hpp" (HPPMERGE)
namespace Math {
    template<floating_point T>
    auto TranslationMatrix(Vec3<T> translation) {
        return Mat4<T>({
            1, 0, 0, translation.x,
            0, 1, 0, translation.y,
            0, 0, 1, translation.z,
            0, 0, 0, 1
        });
    }
    template<floating_point T>
    auto RotationMatrix(Vec3<T> euler_rotation) {
        Mat3<T> mat;
        T sinx = sin(euler_rotation.x);
        T cosx = cos(euler_rotation.x);
        T siny = sin(euler_rotation.y);
        T cosy = cos(euler_rotation.y);
        T sinz = sin(euler_rotation.z);
        T cosz = cos(euler_rotation.z);
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
    template<floating_point T>
    auto ScaleMatrix(Vec3<T> scale) {
        return Mat3<T>({
            scale.x, 0, 0,
            0, scale.y, 0,
            0, 0, scale.z,
        });
    }
    template<floating_point T>
    auto ModelMatrix(Vec3<T> position, Vec3<T> rotation, Vec3<T> scale) {
        auto out = Zero<T, 4>();
        out.insert(ScaleMatrix(scale) * RotationMatrix(rotation), { 0, 0 });
        out.insert(Vec4<T>(position, 1), { 0, 3 });
        return out;
    }
    template<floating_point T>
    auto ViewMatrix(Vec3<T> position, Vec3<T> rotation) {
        Mat4<T> rotate = Identity<T, 4>();
        rotate.insert(transpose(RotationMatrix(rotation)), { 0, 0 });
        Mat4<T> translate = Identity<T, 4>();
        translate.insert(Vec4<T>(-position, 1), { 0, 3 });
        return rotate * translate;
    }
    template<floating_point T>
    auto PerspectiveMatrix(T fov, T aspectRatio, T zNear, T zFar) {
        auto mat = Zero<T, 4>();
        mat.at(0, 0) = 1.0 / tan(fov / 2);
        mat.at(1, 1) = aspectRatio / tan(fov / 2); 
        mat.at(2, 2) = 2 * zFar / (zFar - zNear) - 1;
        mat.at(2, 3) = -2 * zNear * zFar / (zFar - zNear);
        mat.at(3, 2) = 1;
        return mat;
    }
}