// Copyright (c) 2026 Mathis Le Gall
//
// This file is part of RealmPP and is licensed under the MIT License.
// See LICENSE file in the project root for full license information.

/* --- Google Test Includes --- */
#include "gtest/gtest.h"

/* --- RealmPP Includes --- */
#include <realmpp/core/bounding_box.hpp>
#include <realmpp/core/point.hpp>

TEST(bounding_box_test, constructors)
{
    {
        realmpp::bounding_box<int> box;
        realmpp::point<int> default_point;

        EXPECT_EQ(box.top_left(), default_point);
        EXPECT_EQ(box.bottom_left(), default_point);
        EXPECT_EQ(box.top_right(), default_point);
        EXPECT_EQ(box.bottom_right(), default_point);
        EXPECT_EQ(box.center(), default_point);
        EXPECT_EQ(box.width(), 0);
        EXPECT_EQ(box.height(), 0);
        EXPECT_EQ(box.area(), 0);
    }

    {
        realmpp::point<double> top_left(1.5, 2.5);
        realmpp::point<double> bottom_right(4.5, 6.5);
        realmpp::bounding_box<double> box(top_left, bottom_right);

        EXPECT_DOUBLE_EQ(box.top_left().x(), 1.5);
        EXPECT_DOUBLE_EQ(box.top_left().y(), 2.5);
        EXPECT_DOUBLE_EQ(box.bottom_right().x(), 4.5);
        EXPECT_DOUBLE_EQ(box.bottom_right().y(), 6.5);
        EXPECT_DOUBLE_EQ(box.bottom_left().x(), 1.5);
        EXPECT_DOUBLE_EQ(box.bottom_left().y(), 6.5);
        EXPECT_DOUBLE_EQ(box.top_right().x(), 4.5);
        EXPECT_DOUBLE_EQ(box.top_right().y(), 2.5);
        EXPECT_DOUBLE_EQ(box.center().x(), 3.0);
        EXPECT_DOUBLE_EQ(box.center().y(), 4.5);
        EXPECT_DOUBLE_EQ(box.width(), 3.0);
        EXPECT_DOUBLE_EQ(box.height(), 4.0);
        EXPECT_DOUBLE_EQ(box.area(), 12.0);
    }
}

TEST(bounding_box_test, contains)
{
    realmpp::bounding_box<int> box({0, 0}, {10, 10});

    EXPECT_TRUE(box.contains({5, 5}));
    EXPECT_TRUE(box.contains({0, 0}));
    EXPECT_FALSE(box.contains({10, 10}));
    EXPECT_FALSE(box.contains({-1, -1}));
}

TEST(bounding_box_test, intersects)
{
    realmpp::bounding_box<int> box1({0, 0}, {10, 10});
    realmpp::bounding_box<int> box2({5, 5}, {15, 15});
    realmpp::bounding_box<int> box3({10, 10}, {20, 20});
    realmpp::bounding_box<int> box4({-5, -5}, {5, 5});

    EXPECT_TRUE(box1.intersects(box2));
    EXPECT_FALSE(box1.intersects(box3));
    EXPECT_TRUE(box1.intersects(box4));
}
