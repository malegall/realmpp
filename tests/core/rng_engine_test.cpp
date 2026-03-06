// Copyright (c) 2026 Mathis Le Gall
//
// This file is part of RealmPP and is licensed under the MIT License.
// See LICENSE file in the project root for full license information.

/* --- Google Test Includes --- */
#include "gtest/gtest.h"

/* --- RealmPP Includes --- */
#include <realmpp/core/rng_engine.hpp>

TEST(rng_engine_test, reproducibility)
{
    realmpp::rng_engine engine1(12345);
    realmpp::rng_engine engine2(12345);

    EXPECT_EQ(engine1.next(0, 100), engine2.next(0, 100));
    EXPECT_EQ(engine1.next(0.0, 1.0), engine2.next(0.0, 1.0));
}

TEST(rng_engine_test, range)
{
    realmpp::rng_engine engine(12345);

    for (int i{0}; i < 100; ++i)
    {
        int value = engine.next(10, 20);
        EXPECT_GE(value, 10);
        EXPECT_LE(value, 20);
    }

    for (int i{0}; i < 100; ++i)
    {
        double value = engine.next(0.0, 1.0);
        EXPECT_GE(value, 0.0);
        EXPECT_LT(value, 1.0);
    }
}
