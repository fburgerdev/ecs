#pragma once
#include "struct.hpp"

namespace Math {
    // ostream << matrix
    template <typename T, uint N, uint M>
    std::ostream& operator<<(std::ostream& os, const Mat<T, N, M>& mat) {
        // lines
        string lines[N];
        string numbers[N];
        for (uint j = 0; j < M; ++j) {
            // numbers
            for (uint i = 0; i < N; ++i) {
                numbers[i] = std::to_string(mat.at(i, j));
            }
            // max
            uint max = 0;
            for (uint i = 0; i < N; ++i) {
                max = max < numbers[i].size() ? numbers[i].size() : max;
            }
            // padding
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
        // stream
        os << '\n';
        for (uint i = 0; i < N; ++i) {
            os << lines[i] << '|' << '\n';
        }
        return os;
    }
}