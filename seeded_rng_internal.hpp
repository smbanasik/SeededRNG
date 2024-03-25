#ifndef SB_SEEDED_RNG_INTERNAL
#define SB_SEEDED_RNG_INTERNAL

#include <stdint.h>
#include <random>
#include <vector>

struct RNG_INTERNAL {

    RNG_INTERNAL(uint32_t seed) : init_seed(seed) {
        random_engine = std::mt19937(seed);
    }

    std::vector<uint32_t> last_valuesi;
    std::vector<float> last_valuesf;
    uint32_t init_seed;

    std::mt19937 random_engine;
    std::vector<std::uniform_int_distribution<uint32_t>> int_channels;
    std::vector<std::uniform_real_distribution<float>> float_channels;

    uint32_t float2seed(float value) {
        if (value > 10'000)
            return (uint32_t)value;
        else
            return (uint32_t)(value * 10'000);
    }
};
#endif