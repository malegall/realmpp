// Copyright (c) 2026 Mathis Le Gall
//
// This file is part of RealmPP and is licensed under the MIT License.
// See LICENSE file in the project root for full license information.

#pragma once

/* --- Standard Includes --- */
#include <cmath>
#include <iostream>

/* --- RealmPP Includes --- */
#include <realmpp/core/traits.hpp>

namespace realmpp
{

/**
 * @class point
 * @ingroup core
 *
 * @brief Represents a point in a 2D space.
 *
 * @tparam T The numeric type for coordinates (must be arithmetic).
 *
 * @file point.hpp
 * @author Mathis Le Gall
 * @date March 6th, 2026
 */
template <traits::arithmetic T>
class point
{
public:
    using value_type = T;

    /**
     * @brief Constructor.
     */
    constexpr point(T x = T{}, T y = T{}) noexcept : x_(x), y_(y) {}

    /**
     * @brief Converting constructor.
     */
    template <traits::arithmetic_convertible<T> U>
    constexpr explicit point(point<U> const& other) noexcept
        : x_(static_cast<T>(other.x())), y_(static_cast<T>(other.y()))
    {}

    /**
     * @brief Destructor.
     */
    constexpr ~point() noexcept = default;

    /**
     * @brief Gets the x-coordinate.
     */
    [[nodiscard]] constexpr T x() const noexcept { return x_; }

    /**
     * @brief Gets the y-coordinate.
     */
    [[nodiscard]] constexpr T y() const noexcept { return y_; }

    /**
     * @brief Sets the x-coordinate.
     */
    constexpr void set_x(T x) noexcept { x_ = x; }

    /**
     * @brief Sets the y-coordinate.
     */
    constexpr void set_y(T y) noexcept { y_ = y; }

    /**
     * @brief Defaulted spaceship operator — provides ==, !=, <, <=, >, >=.
     * @note For floating-point types, use near_equal().
     */
    constexpr auto operator<=>(point const&) const noexcept = default;
    constexpr bool operator==(point const&) const noexcept = default;

    /**
     * @brief Approximate equality for floating-point positions.
     */
    [[nodiscard]] constexpr bool near_equal(
        point const& other, T epsilon = std::numeric_limits<T>::epsilon()) const noexcept
        requires traits::floating_point<T>
    {
        return std::abs(x_ - other.x_) <= epsilon && std::abs(y_ - other.y_) <= epsilon;
    }

    /**
     * @brief Addition operator.
     */
    [[nodiscard]] constexpr point operator+(point const& other) const noexcept
    {
        return {x_ + other.x_, y_ + other.y_};
    }

    /**
     * @brief Subtraction operator.
     */
    [[nodiscard]] constexpr point operator-(point const& other) const noexcept
    {
        return {x_ - other.x_, y_ - other.y_};
    }

    /**
     * @brief Scalar multiplication.
     */
    [[nodiscard]] constexpr point operator*(T scalar) const noexcept
    {
        return {x_ * scalar, y_ * scalar};
    }

    /**
     * @brief Scalar division.
     * @pre scalar != 0 for integral types.
     */
    [[nodiscard]] constexpr point operator/(T scalar) const noexcept
    {
        return {x_ / scalar, y_ / scalar};
    }

    /**
     * @brief Unary negation.
     */
    [[nodiscard]] constexpr point operator-() const noexcept { return {-x_, -y_}; }

    /**
     * @brief Computes the squared Euclidean distance to another point.
     */
    [[nodiscard]] constexpr T distance_squared(point const& other) const noexcept
    {
        const T dx = x_ - other.x_;
        const T dy = y_ - other.y_;
        return dx * dx + dy * dy;
    }

    /**
     * @brief Computes the Euclidean distance to another point.
     */
    [[nodiscard]] double distance(point const& other) const noexcept
    {
        return std::sqrt(static_cast<double>(distance_squared(other)));
    }

    /**
     * @brief Output stream operator for easy debugging.
     */
    friend std::ostream& operator<<(std::ostream& os, point const& pos)
    {
        os << "(" << pos.x_ << ", " << pos.y_ << ")";
        return os;
    }

private:
    T x_{};  ///< X coordinate
    T y_{};  ///< Y coordinate
};

/**
 * @brief Scalar multiplication (commutative).
 */
template <traits::arithmetic T>
[[nodiscard]] constexpr point<T> operator*(T scalar, point<T> const& pos) noexcept
{
    return pos * scalar;
}

namespace traits
{
/**
 * @brief Concept for callback functions that can be invoked with a point<T>.
 */
template <typename Func, typename T>
concept point_callback = std::invocable<Func, point<T>>;
}  // namespace traits

}  // namespace realmpp
