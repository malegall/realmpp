// Copyright (c) 2026 Mathis Le Gall
//
// This file is part of RealmPP and is licensed under the MIT License.
// See LICENSE file in the project root for full license information.

#pragma once

/* --- Standard Includes --- */
#include <concepts>
#include <type_traits>

/**
 * @namespace traits
 * @ingroup core
 *
 * @brief Defines concepts for type traits used in RealmPP.
 *
 * @file traits.hpp
 * @author Mathis Le Gall
 * @date March 6th, 2026
 */
namespace realmpp::traits
{
/**
 * @brief Concept for arithmetic types.
 */
template <typename T>
concept arithmetic = std::is_arithmetic_v<T>;

/**
 * @brief Concept for arithmetic convertible types.
 */
template <typename T, typename U>
concept arithmetic_convertible = arithmetic<T> && arithmetic<U> && std::is_convertible_v<T, U>;

/**
 * @brief Concept for floating-point types.
 */
template <typename T>
concept floating_point = std::floating_point<T>;

/**
 * @brief Concept for containers that can be accessed like a 1D array of T.
 */
template <typename Container, typename T>
concept grid_container = requires(Container& c, Container const& cc, std::size_t i) {
    {
        c[i]
    } -> std::same_as<T&>;
    {
        cc[i]
    } -> std::same_as<T const&>;
    {
        cc.size()
    } -> std::convertible_to<std::size_t>;
};

/**
 * @brief Concept for containers that support resizing and reassignment.
 */
template <typename Container>
concept resizable = std::movable<Container> &&
                    requires(Container& c, std::size_t n, typename Container::value_type v) {
                        c.assign(n, v);
                        c = Container(n, v);
                    };
}  // namespace realmpp::traits
