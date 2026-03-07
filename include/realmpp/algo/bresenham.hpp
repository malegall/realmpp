// Copyright (c) 2026 Mathis Le Gall
//
// This file is part of RealmPP and is licensed under the MIT License.
// See LICENSE file in the project root for full license information.

#pragma once

/* --- Standard Includes --- */
#include <utility>

/* --- RealmPP Includes --- */
#include "realmpp/core/point.hpp"
#include "realmpp/core/traits.hpp"

/**
 * @namespace bresenham
 * @ingroup algo
 *
 * @brief Implements Bresenham's line algorithm.
 *
 * @file bresenham.hpp
 * @author Mathis Le Gall
 * @date March 7th, 2026
 */
namespace realmpp::bresenham
{

/**
 * @brief Computes a line between two points using Bresenham's algorithm.
 * @tparam T The integral type for coordinates (defaults to int).
 */
template <traits::integral T = int, traits::point_callback<T> Func>
constexpr void draw_line(point<T> start, point<T> end, Func&& callback)
{
    auto constexpr_abs = [](T v) constexpr -> T { return v < 0 ? -v : v; };

    T x1 = start.x();
    T y1 = start.y();
    const T x2 = end.x();
    const T y2 = end.y();

    const T dx = constexpr_abs(x2 - x1);
    const T dy = -constexpr_abs(y2 - y1);
    const T sx = (x1 < x2) ? 1 : -1;
    const T sy = (y1 < y2) ? 1 : -1;

    T err = dx + dy;

    while (true)
    {
        std::forward<Func>(callback)(point<T>{x1, y1});

        if (x1 == x2 && y1 == y2) break;

        const T e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            x1 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

/**
 * @brief Computes a line between two points and returns the points as a vector.
 * @tparam T The integral type for coordinates (defaults to int).
 */
template <traits::integral T = int>
constexpr auto line(point<T> start, point<T> end)
{
    std::vector<point<T>> points;
    draw_line(start, end, [&](point<T> p) { points.push_back(p); });
    return points;
}

}  // namespace realmpp::bresenham
