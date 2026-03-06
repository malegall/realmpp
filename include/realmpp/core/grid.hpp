// Copyright (c) 2026 Mathis Le Gall
//
// This file is part of RealmPP and is licensed under the MIT License.
// See LICENSE file in the project root for full license information.

#pragma once

/* --- Standard Includes --- */
#include <cstddef>
#include <span>
#include <stdexcept>
#include <vector>

/* --- RealmPP Includes --- */
#include <realmpp/core/point.hpp>
#include <realmpp/core/traits.hpp>

namespace realmpp
{

/**
 * @class grid
 * @ingroup core
 *
 * @brief Represents a grid in a 2D space.
 *
 * @tparam T The numeric type for coordinates (must be arithmetic).
 *
 * @file grid.hpp
 * @author Mathis Le Gall
 * @date March 7th, 2026
 */
template <typename T, traits::grid_container<T> Container = std::vector<T>>
class grid
{
public:
    using value_type = T;
    using iterator = typename Container::iterator;
    using const_iterator = typename Container::const_iterator;

    /**
     * @brief Constructor to create a grid with specified width and height.
     */
    constexpr grid(std::size_t width = 0, std::size_t height = 0, T const& initial_value = T{})
        : width_(width), height_(height), data_{}
    {
        if constexpr (traits::resizable<Container>)
            data_.assign(width * height, initial_value);
        else
        {
            if (width * height != data_.size())
                throw std::invalid_argument("Grid dimensions do not match static container size");
            std::fill(data_.begin(), data_.end(), initial_value);
        }
    }

    /**
     * @brief Destructor.
     */
    constexpr ~grid() noexcept = default;

    // --- Copy and Move operations ---
    constexpr grid(grid const& other) = default;
    constexpr grid(grid&& other) noexcept = default;
    constexpr grid& operator=(grid const& other) = default;
    constexpr grid& operator=(grid&& other) noexcept = default;

    /**
     * @brief Equality operator.
     */
    constexpr bool operator==(grid const& other) const noexcept = default;

    /**
     * @brief Gets the value at the specified point coordinates.
     * @note This does not check bounds. Use at() for checked access.
     */
    constexpr T& operator[](point<std::size_t> const& pos) { return data_[index(pos)]; }

    /**
     * @brief Gets the value at the specified point coordinates (const version).
     * @note This does not check bounds. Use at() for checked access.
     */
    constexpr T const& operator[](point<std::size_t> const& pos) const { return data_[index(pos)]; }

    /**
     * @brief Gets the value at the specified point coordinates.
     * @throws std::out_of_range if the coordinates are out of bounds.
     */
    [[nodiscard]] constexpr T& at(point<std::size_t> const& pos)
    {
        if (!contains(pos))
            throw std::out_of_range("Grid coordinates out of range: (" + std::to_string(pos.x()) +
                                    ", " + std::to_string(pos.y()) + ")");
        return data_[index(pos)];
    }

    /**
     * @brief Gets the value at the specified point coordinates (const version).
     * @throws std::out_of_range if the coordinates are out of bounds.
     */
    [[nodiscard]] constexpr T const& at(point<std::size_t> const& pos) const
    {
        if (!contains(pos))
            throw std::out_of_range("Grid coordinates out of range: (" + std::to_string(pos.x()) +
                                    ", " + std::to_string(pos.y()) + ")");
        return data_[index(pos)];
    }

    /**
     * @brief Sets the value at the specified point coordinates.
     */
    constexpr void set(point<std::size_t> const& pos, T value) { data_.at(index(pos)) = value; }

    /**
     * @brief Checks if grid contains the specified point coordinates.
     */
    [[nodiscard]] constexpr bool contains(point<std::size_t> const& pos) const noexcept
    {
        return pos.x() < width_ && pos.y() < height_;
    }

    /**
     * @brief Fills the entire grid with the specified value.
     */
    constexpr void fill(T const& value) noexcept { std::fill(data_.begin(), data_.end(), value); }

    /**
     * @brief Clears the grid by filling it with default-constructed values.
     */
    constexpr void clear() noexcept { std::fill(data_.begin(), data_.end(), T{}); }

    /**
     * @brief Resizes the grid. Destroys current contents.
     */
    constexpr void assign(std::size_t width, std::size_t height, T const& initial_value = T{})
        requires traits::resizable<Container>
    {
        width_ = width;
        height_ = height;
        data_.assign(width * height, initial_value);
    }

    /**
     * @brief Resizes the grid. Keeps current contents.
     */
    constexpr void resize(std::size_t width, std::size_t height, T const& new_value)
        requires traits::resizable<Container>
    {
        if (width == width_ && height == height_) return;

        Container new_data(width * height, new_value);

        const std::size_t copy_width = std::min(width, width_);
        const std::size_t copy_height = std::min(height, height_);

        for (auto y{0}; y < copy_height; ++y)
            for (auto x{0}; x < copy_width; ++x) new_data[y * width + x] = data_[index({x, y})];

        width_ = width;
        height_ = height;
        data_ = std::move(new_data);
    }

    /**
     * @brief Gets the width of the grid.
     */
    [[nodiscard]] constexpr std::size_t width() const noexcept { return width_; }

    /**
     * @brief Gets the height of the grid.
     */
    [[nodiscard]] constexpr std::size_t height() const noexcept { return height_; }

    /**
     * @brief Gets the total number of elements in the grid.
     */
    [[nodiscard]] constexpr std::size_t size() const noexcept { return data_.size(); }

    /**
     * @brief Checks if the grid is empty.
     */
    [[nodiscard]] constexpr bool empty() const noexcept { return data_.empty(); }

    /**
     * @brief Returns a modifiable std::span covering the entire grid data.
     */
    [[nodiscard]] constexpr std::span<T> data() noexcept { return data_; }

    /**
     * @brief Returns a read-only std::span covering the entire grid data.
     */
    [[nodiscard]] constexpr std::span<const T> data() const noexcept { return data_; }

    // --- Iterators ---
    [[nodiscard]] constexpr iterator begin() noexcept { return data_.begin(); }
    [[nodiscard]] constexpr const_iterator begin() const noexcept { return data_.begin(); }
    [[nodiscard]] constexpr const_iterator cbegin() const noexcept { return data_.cbegin(); }

    [[nodiscard]] constexpr iterator end() noexcept { return data_.end(); }
    [[nodiscard]] constexpr const_iterator end() const noexcept { return data_.end(); }
    [[nodiscard]] constexpr const_iterator cend() const noexcept { return data_.cend(); }

private:
    std::size_t width_;   ///< Width of the grid
    std::size_t height_;  ///< Height of the grid
    Container data_;      ///< Flat vector to store grid values

    /**
     * @brief Converts 2D point coordinates to a linear index in the data vector.
     */
    [[nodiscard]] constexpr std::size_t index(point<std::size_t> const& pos) const noexcept
    {
        return pos.y() * width_ + pos.x();
    }
};

}  // namespace realmpp
