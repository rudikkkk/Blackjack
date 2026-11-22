#pragma once
#include <cstdint>

namespace front {

struct Point {
    int x{};
    int y{};
};

struct Size {
    int width{};
    int height{};
};

struct Rect {
    int x{};
    int y{};
    int width{};
    int height{};
};

struct Color {
    std::uint8_t r{}, g{}, b{}, a{255};
};

namespace colors {
inline constexpr Color white{255, 255, 255};
inline constexpr Color black{0, 0, 0};
inline constexpr Color red{255, 0, 0};
inline constexpr Color green{0, 255, 0};
inline constexpr Color blue{0, 0, 255};
inline constexpr Color gray{128, 128, 128};
} // namespace colors

} // namespace front