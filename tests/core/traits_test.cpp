// Copyright (c) 2026 Mathis Le Gall
//
// This file is part of RealmPP and is licensed under the MIT License.
// See LICENSE file in the project root for full license information.

/* --- Google Test Includes --- */
#include "gtest/gtest.h"

/* --- Standard Includes --- */
#include <array>
#include <list>
#include <string>
#include <vector>

/* --- RealmPP Includes --- */
#include <realmpp/core/traits.hpp>

TEST(traits_test, arithmetic_concept)
{
    static_assert(realmpp::traits::arithmetic<int>,
                  "[arithmetic_concept] int should satisfy the arithmetic concept");
    static_assert(realmpp::traits::arithmetic<double>,
                  "[arithmetic_concept] double should satisfy the arithmetic concept");
    static_assert(!realmpp::traits::arithmetic<std::string>,
                  "[arithmetic_concept] std::string should not satisfy the arithmetic concept");
}

TEST(traits_test, arithmetic_convertible_concept)
{
    static_assert(realmpp::traits::arithmetic_convertible<int, double>,
                  "[arithmetic_convertible_concept] int should be convertible to double");
    static_assert(realmpp::traits::arithmetic_convertible<double, int>,
                  "[arithmetic_convertible_concept] double should be convertible to int");
    static_assert(!realmpp::traits::arithmetic_convertible<int, std::string>,
                  "[arithmetic_convertible_concept] int should not be convertible to std::string");
    static_assert(!realmpp::traits::arithmetic_convertible<std::string, int>,
                  "[arithmetic_convertible_concept] std::string should not be convertible to int");
}

TEST(traits_test, floating_point_concept)
{
    static_assert(realmpp::traits::floating_point<double>,
                  "[floating_point_concept] double should satisfy the floating_point concept");
    static_assert(realmpp::traits::floating_point<float>,
                  "[floating_point_concept] float should satisfy the floating_point concept");
    static_assert(!realmpp::traits::floating_point<int>,
                  "[floating_point_concept] int should not satisfy the floating_point concept");
}

TEST(traits_test, grid_container_concept)
{
    static_assert(
        realmpp::traits::grid_container<std::vector<int>, int>,
        "[grid_container_concept] std::vector<int> should satisfy the grid_container concept");
    static_assert(realmpp::traits::grid_container<std::array<double, 10>, double>,
                  "[grid_container_concept] std::array<double, 10> should satisfy the "
                  "grid_container concept");
    static_assert(
        !realmpp::traits::grid_container<std::list<int>, int>,
        "[grid_container_concept] std::list<int> should not satisfy the grid_container concept");
}

TEST(traits_test, resizable_concept)
{
    static_assert(realmpp::traits::resizable<std::vector<int>>,
                  "[resizable_concept] std::vector<int> should satisfy the resizable concept");
    static_assert(
        !realmpp::traits::resizable<std::array<int, 10>>,
        "[resizable_concept] std::array<int, 10> should not satisfy the resizable concept");
}
