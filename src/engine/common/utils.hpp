#pragma once

#include "index_vector.hpp"
#include <sstream>

/**
 * @brief Convert a value to a string
 * 
 * @tparam T type of the value
 * @param v value to convert
 * @return std::string string representation of the value
 */
template<typename U, typename T>
U to(const T& v) {
    return static_cast<U>(v);
}

/**
 * @brief Convert a value to a string
 * 
 * @tparam T type of the value
 * @param v value to convert
 * @return std::string string representation of the value
 */
template<typename T>
using CIVector = civ::Vector<T>;

/**
 * @brief Convert a value to a string
 * 
 * @tparam T type of the value
 * @param v value to convert
 * @return std::string string representation of the value
 */
template<typename T>
sf::Vector2f toVector2f(sf::Vector2<T> v) {
    return {to<float>(v.x), to<float>(v.y)};
};
