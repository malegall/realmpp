// Copyright (c) 2026 Mathis Le Gall
//
// This file is part of RealmPP and is licensed under the MIT License.
// See LICENSE file in the project root for full license information.

#pragma once

/* --- RealmPP Includes --- */
#include <realmpp/core/point.hpp>
#include <realmpp/core/traits.hpp>

namespace realmpp
{

/**
 * @class bounding_box
 * @ingroup core
 *
 * @brief Represents an axis-aligned bounding box in 2D space.
 *
 * @tparam T The numeric type for coordinates (must be arithmetic).
 *
 * @file bounding_box.hpp
 * @author Mathis Le Gall
 * @date March 7th, 2026
 */
template <traits::arithmetic T>
class bounding_box
{
public:
    using value_type = T;

    /**
     * @brief Constructor.
     * @pre top_left.x() <= bottom_right.x() and top_left.y() <= bottom_right.y()
     */
    constexpr bounding_box(point<T> const& top_left = point<T>{},
                           point<T> const& bottom_right = point<T>{}) noexcept
        : top_left_(top_left), bottom_right_(bottom_right)
    {}

    /**
     * @brief Destructor.
     */
    constexpr ~bounding_box() noexcept = default;

    /**
     * @brief Gets the top-left corner of the bounding box.
     */
    [[nodiscard]] constexpr point<T> top_left() const noexcept { return top_left_; }

    /**
     * @brief Gets the bottom-left corner of the bounding box.
     */
    [[nodiscard]] constexpr point<T> bottom_left() const noexcept
    {
        return {top_left_.x(), bottom_right_.y()};
    }

    /**
     * @brief Gets the top-right corner of the bounding box.
     */
    [[nodiscard]] constexpr point<T> top_right() const noexcept
    {
        return {bottom_right_.x(), top_left_.y()};
    }

    /**
     * @brief Gets the bottom-right corner of the bounding box.
     */
    [[nodiscard]] constexpr point<T> bottom_right() const noexcept { return bottom_right_; }

    /**
     * @brief Gets the center point of the bounding box.
     */
    [[nodiscard]] constexpr point<T> center() const noexcept
    {
        return {(top_left_.x() + bottom_right_.x()) / static_cast<T>(2),
                (top_left_.y() + bottom_right_.y()) / static_cast<T>(2)};
    }

    /**
     * @brief Gets the width of the bounding box.
     */
    [[nodiscard]] constexpr T width() const noexcept { return bottom_right_.x() - top_left_.x(); }

    /**
     * @brief Gets the height of the bounding box.
     */
    [[nodiscard]] constexpr T height() const noexcept { return bottom_right_.y() - top_left_.y(); }

    /**
     * @brief Gets the area of the bounding box.
     */
    [[nodiscard]] constexpr T area() const noexcept { return this->width() * this->height(); }

    /**
     * @brief Checks if a point is contained within the bounding box (inclusive).
     */
    [[nodiscard]] constexpr bool contains(point<T> const& point) const noexcept
    {
        return point.x() >= top_left_.x() && point.x() < bottom_right_.x() &&
               point.y() >= top_left_.y() && point.y() < bottom_right_.y();
    }

    /**
     * @brief Checks if this bounding box intersects (overlaps) with another bounding box.
     */
    [[nodiscard]] constexpr bool intersects(bounding_box const& other) const noexcept
    {
        return top_left_.x() < other.bottom_right_.x() && bottom_right_.x() > other.top_left_.x() &&
               top_left_.y() < other.bottom_right_.y() && bottom_right_.y() > other.top_left_.y();
    }

private:
    point<T> top_left_;      ///< Top-left corner
    point<T> bottom_right_;  ///< Bottom-right corner
};

}  // namespace realmpp
