#pragma once
#include "index_vector.hpp"
#include <sstream>


template<typename U, typename T>
U to(const T& v) {
    return static_cast<U>(v);
}


template<typename T>
using CIVector = civ::Vector<T>;

template<typename T>
sf::Vector2f toVector2f(sf::Vector2<T> v) {
    return {to<float>(v.x), to<float>(v.y)};
}
