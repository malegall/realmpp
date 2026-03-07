// Copyright (c) 2026 Mathis Le Gall
//
// This file is part of RealmPP and is licensed under the MIT License.
// See LICENSE file in the project root for full license information.

#pragma once

/* --- Standard Includes --- */
#include <cstdint>
#include <random>

/* --- RealmPP Includes --- */
#include <realmpp/core/traits.hpp>

namespace realmpp
{

/**
 * @class rng_engine
 * @ingroup core
 *
 * @brief A predictable and reproducible random number generator.
 *
 * @file rng_engine.hpp
 * @author malegall
 * @date March 6th, 2026
 */
class rng_engine
{
public:
    /**
     * @brief Constructs the engine with a specific seed.
     */
    explicit rng_engine(std::uint32_t seed) : seed_(seed), engine_(seed) {}

    /**
     * @brief Constructs the engine with a random seed.
     */
    rng_engine()
    {
        seed_ = std::random_device{}();
        engine_.seed(seed_);
    }

    /**
     * @brief Generates a random integer in the range [min, max].
     */
    template <traits::integral T>
    [[nodiscard]] T next(T min, T max)
    {
        std::uniform_int_distribution<T> dist(min, max);
        return dist(engine_);
    }

    /**
     * @brief Generates a random floating-point number in the range [min, max).
     */
    template <traits::floating_point T>
    [[nodiscard]] T next(T min, T max)
    {
        std::uniform_real_distribution<T> dist(min, max);
        return dist(engine_);
    }

    /**
     * @brief Gets the std::mt19937 engine.
     */
    [[nodiscard]] std::mt19937& engine() noexcept { return engine_; }

private:
    std::uint32_t seed_{0};  ///< Seed for the PRNG
    std::mt19937 engine_;    ///< Mersenne Twister engine
};

}  // namespace realmpp
