// Copyright (c) 2026 Mathis Le Gall
//
// This file is part of RealmPP and is licensed under the MIT License.
// See LICENSE file in the project root for full license information.

/* --- Google Test Includes --- */
#include "gtest/gtest.h"

/* --- Standard Includes --- */
#include <vector>

/* --- RealmPP Includes --- */
#include <realmpp/algo/bresenham.hpp>

TEST(bresenham_test, horizontal_line)
{
    std::vector<realmpp::point<int>> path;
    realmpp::point<int> start{1, 2};
    realmpp::point<int> end{4, 2};

    realmpp::bresenham::draw_line(start, end, [&path](auto const& p) { path.push_back(p); });

    ASSERT_EQ(path.size(), 4);
    EXPECT_EQ(path[0], (realmpp::point<int>{1, 2}));
    EXPECT_EQ(path[1], (realmpp::point<int>{2, 2}));
    EXPECT_EQ(path[2], (realmpp::point<int>{3, 2}));
    EXPECT_EQ(path[3], (realmpp::point<int>{4, 2}));
}

TEST(bresenham_test, vertical_line)
{
    std::vector<realmpp::point<int>> path;
    realmpp::point<int> start{3, 1};
    realmpp::point<int> end{3, 4};

    realmpp::bresenham::draw_line(start, end, [&path](auto const& p) { path.push_back(p); });

    ASSERT_EQ(path.size(), 4);
    EXPECT_EQ(path[0], (realmpp::point<int>{3, 1}));
    EXPECT_EQ(path[1], (realmpp::point<int>{3, 2}));
    EXPECT_EQ(path[2], (realmpp::point<int>{3, 3}));
    EXPECT_EQ(path[3], (realmpp::point<int>{3, 4}));
}

TEST(bresenham_test, diagonal_line)
{
    realmpp::point<int> start{1, 1};
    realmpp::point<int> end{4, 4};

    auto line = realmpp::bresenham::line(start, end);

    ASSERT_EQ(line.size(), 4);
    EXPECT_EQ(line[0], (realmpp::point<int>{1, 1}));
    EXPECT_EQ(line[1], (realmpp::point<int>{2, 2}));
    EXPECT_EQ(line[2], (realmpp::point<int>{3, 3}));
    EXPECT_EQ(line[3], (realmpp::point<int>{4, 4}));
}

TEST(bresenham_test, reverse_line)
{
    realmpp::point<int> start{2, 5};
    realmpp::point<int> end{0, 0};

    auto line = realmpp::bresenham::line(start, end);

    ASSERT_EQ(line.front(), start);
    ASSERT_EQ(line.back(), end);
    ASSERT_EQ(line.size(), 6);
}
