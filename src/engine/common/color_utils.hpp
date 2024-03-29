#pragma once

#include <SFML/Graphics/Color.hpp>
#include <cmath>

#include "utils.hpp"

/**
 * @brief Utility class for colors
 * 
 */
struct ColorUtils {
    constexpr static float PI = 3.141592653f;

    /**
     * @brief Create a color object
     * 
     * @tparam T type of the color components
     * @param r red component
     * @param g green component
     * @param b blue component
     * @return sf::Color color object
     */
    template<typename T>
    static sf::Color createColor(T r, T g, T b) {
        return { to<uint8_t>(r), to<uint8_t>(g), to<uint8_t>(b) };
    }

    /**
     * @brief Create a color object
     * 
     * @tparam T type of the color components
     * @param r red component
     * @param g green component
     * @param b blue component
     * @param a alpha component
     * @return sf::Color color object
     */
    static sf::Color getRainbow(float t) {
        const float r = std::sin(t);
        const float g = std::sin(t + 0.33f * 2.0f * PI);
        const float b = std::sin(t + 0.66f * 2.0f * PI);
        return createColor(255 * r * r, 255 * g * g, 255 * b * b);
    }
};
