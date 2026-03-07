// Copyright (c) 2026 Mathis Le Gall
//
// This file is part of RealmPP and is licensed under the MIT License.
// See LICENSE file in the project root for full license information.

/* --- Google Test Includes --- */
#include "gtest/gtest.h"

/* --- RealmPP Includes --- */
#include <realmpp/core/point.hpp>

TEST(point_test, constructors)
{
    {
        realmpp::point<int> p;

        EXPECT_EQ(p.x(), 0);
        EXPECT_EQ(p.y(), 0);
    }

    {
        realmpp::point<double> p(3.5, -2.1);

        EXPECT_DOUBLE_EQ(p.x(), 3.5);
        EXPECT_DOUBLE_EQ(p.y(), -2.1);
    }

    {
        realmpp::point<int> p1(4, 5);
        realmpp::point<double> p2(p1);

        EXPECT_DOUBLE_EQ(p2.x(), 4.0);
        EXPECT_DOUBLE_EQ(p2.y(), 5.0);
    }
}

TEST(point_test, comparisons)
{
    realmpp::point<float> p1(1.0f, 2.0f);
    realmpp::point<float> p2(1.1f, 2.1f);
    realmpp::point<float> p3(1.0001f, 2.0001f);

    EXPECT_FALSE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
    EXPECT_TRUE(p1.near_equal(p3, 0.0005f));
    EXPECT_FALSE(p1.near_equal(p2, 0.0005f));
}

TEST(point_test, operators)
{
    realmpp::point<double> p1(1.0, 2.0);
    realmpp::point<double> p2(.5, 1.5);
    const double scalar = 2.0;

    EXPECT_DOUBLE_EQ((p1 + p2).x(), 1.5);
    EXPECT_DOUBLE_EQ((p1 + p2).y(), 3.5);
    EXPECT_DOUBLE_EQ((p1 - p2).x(), 0.5);
    EXPECT_DOUBLE_EQ((p1 - p2).y(), 0.5);
    EXPECT_DOUBLE_EQ((p1 * scalar).x(), 2.0);
    EXPECT_DOUBLE_EQ((p1 * scalar).y(), 4.0);
    EXPECT_DOUBLE_EQ((scalar * p1).x(), 2.0);
    EXPECT_DOUBLE_EQ((scalar * p1).y(), 4.0);
    EXPECT_DOUBLE_EQ((p1 / scalar).x(), 0.5);
    EXPECT_DOUBLE_EQ((p1 / scalar).y(), 1.0);
    EXPECT_DOUBLE_EQ((-p1).x(), -1.0);
    EXPECT_DOUBLE_EQ((-p1).y(), -2.0);
}

TEST(point_test, distances)
{
    realmpp::point<double> p1(0.0, 0.0);
    realmpp::point<double> p2(3.0, 4.0);

    EXPECT_DOUBLE_EQ(p1.distance_squared(p2), 25.0);
    EXPECT_DOUBLE_EQ(p1.distance(p2), 5.0);
}
