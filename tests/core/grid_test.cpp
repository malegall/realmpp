// Copyright (c) 2026 Mathis Le Gall
//
// This file is part of RealmPP and is licensed under the MIT License.
// See LICENSE file in the project root for full license information.

/* --- Google Test Includes --- */
#include "gtest/gtest.h"

/* --- Standard Includes --- */
#include <string>

/* --- RealmPP Includes --- */
#include <realmpp/core/grid.hpp>

TEST(grid_test, constructors)
{
    {
        realmpp::grid<int> grid;
        EXPECT_EQ(grid.width(), 0);
        EXPECT_EQ(grid.height(), 0);
        EXPECT_EQ(grid.size(), 0);
        EXPECT_TRUE(grid.empty());
    }

    {
        realmpp::grid<double> grid(3, 4);
        EXPECT_EQ(grid.width(), 3);
        EXPECT_EQ(grid.height(), 4);
        EXPECT_EQ(grid.size(), 12);
        EXPECT_FALSE(grid.empty());

        for (auto y{0}; y < grid.height(); ++y)
            for (auto x{0}; x < grid.width(); ++x)
                EXPECT_DOUBLE_EQ(grid.at(realmpp::point<std::size_t>(x, y)), 0.0);
    }

    {
        constexpr auto test_compile_time_grid = []() consteval {
            realmpp::grid<int, std::array<int, 9>> static_grid(3, 3);
            static_grid.at(realmpp::point<std::size_t>{1, 1}) = 29;
            return static_grid;
        };
        constexpr auto grid = test_compile_time_grid();
        static_assert(grid.width() == 3, "[constructors] width should be 3");
        static_assert(grid.height() == 3, "[constructors] height should be 3");
        static_assert(grid.size() == 9, "[constructors] size should be 9");
        static_assert(grid.at(realmpp::point<std::size_t>{1, 1}) == 29,
                      "[constructors] center value should be 29");
    }
}

TEST(grid_test, copy_and_move)
{
    realmpp::grid<std::string> original(2, 2, "test");
    realmpp::grid<std::string> copyC(original);
    realmpp::grid<std::string> copyA = original;
    EXPECT_EQ(copyA, original);
    EXPECT_EQ(copyC, original);

    realmpp::grid<std::string> movedC(std::move(copyC));
    realmpp::grid<std::string> movedA = std::move(original);
    EXPECT_EQ(movedA, copyA);
    EXPECT_EQ(movedC, copyA);
    EXPECT_TRUE(original.empty());
    EXPECT_TRUE(copyC.empty());
}

TEST(grid_test, element_access)
{
    realmpp::grid<char> grid(2, 2, 'a');
    EXPECT_EQ(grid.at(realmpp::point<std::size_t>(0, 0)), 'a');
    EXPECT_EQ(grid.at(realmpp::point<std::size_t>(1, 0)), 'a');
    EXPECT_EQ(grid.at(realmpp::point<std::size_t>(0, 1)), 'a');
    EXPECT_EQ(grid.at(realmpp::point<std::size_t>(1, 1)), 'a');
    EXPECT_THROW(static_cast<void>(grid.at(realmpp::point<std::size_t>(2, 0))), std::out_of_range);

    grid.set(realmpp::point<std::size_t>(1, 0), 'b');
    EXPECT_EQ(grid.at(realmpp::point<std::size_t>(1, 0)), 'b');

    grid[realmpp::point<std::size_t>(0, 1)] = 'c';
    EXPECT_EQ(grid[realmpp::point<std::size_t>(0, 1)], 'c');
}

TEST(grid_test, contains)
{
    realmpp::grid<int> grid(3, 3);
    EXPECT_TRUE(grid.contains(realmpp::point<std::size_t>(0, 0)));
    EXPECT_TRUE(grid.contains(realmpp::point<std::size_t>(2, 2)));
    EXPECT_FALSE(grid.contains(realmpp::point<std::size_t>(3, 0)));
}

TEST(grid_test, fill_and_clear)
{
    realmpp::grid<int> grid(3, 3);

    grid.fill(29);
    for (const auto& cell : grid) EXPECT_EQ(cell, 29);

    grid.clear();
    for (const auto& cell : grid) EXPECT_EQ(cell, 0);
}

TEST(grid_test, resize)
{
    realmpp::grid<std::string> grid(2, 2, "hello");
    grid.assign(3, 3, "world");

    EXPECT_EQ(grid.width(), 3);
    EXPECT_EQ(grid.height(), 3);
    EXPECT_FALSE(grid.empty());

    for (const auto& cell : grid) EXPECT_EQ(cell, "world");
}

TEST(grid_test, equality)
{
    realmpp::grid<int> grid1(2, 2, 42);
    realmpp::grid<int> grid2(2, 2, 42);
    realmpp::grid<int> grid3(2, 2, 43);

    EXPECT_EQ(grid1, grid2);
    EXPECT_NE(grid1, grid3);
}
