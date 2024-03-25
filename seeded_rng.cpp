#include "seeded_rng_interface.hpp"

#include <stdint.h>
#include <random>

#include "seeded_rng_internal.hpp"

SeededRNG::SeededRNG(uint32_t seed) {

    this->internal = new RNG_INTERNAL(seed);
}
SeededRNG::~SeededRNG() {
    
    delete this->internal;
}
void SeededRNG::add_channeli(uint32_t rand_val, uint32_t minimum, uint32_t maximum) {

    internal->int_channels.emplace_back(minimum, maximum);
    this->internal->random_engine.seed(this->internal->init_seed + rand_val);
    uint32_t start_val = internal->int_channels.back()(this->internal->random_engine);
    internal->last_valuesi.push_back(start_val);
}
void SeededRNG::add_channelf(uint32_t rand_val, float minimum, float maximum) {

    internal->float_channels.emplace_back(minimum, maximum);
    this->internal->random_engine.seed(this->internal->init_seed + rand_val);
    float start_val = internal->float_channels.back()(this->internal->random_engine);
    internal->last_valuesf.push_back(start_val);
}
void SeededRNG::config_channeli(uint32_t index, uint32_t minimum, uint32_t maximum) {

    internal->int_channels[index] = std::uniform_int_distribution<uint32_t>(minimum, maximum);
}
void SeededRNG::config_channelf(uint32_t index, float minimum, float maximum) {

    internal->float_channels[index] = std::uniform_real_distribution<float>(minimum, maximum);
}
void SeededRNG::remove_channeli(uint32_t index) {

    internal->int_channels.erase(internal->int_channels.begin() + index);
}
void SeededRNG::remove_channelf(uint32_t index) {

    internal->float_channels.erase(internal->float_channels.begin() + index);
}
uint32_t SeededRNG::get_num_channelsi() {

    return internal->int_channels.size();
}
uint32_t SeededRNG::get_num_channelsf() {

    return internal->float_channels.size();
}
uint32_t SeededRNG::use_channeli(uint32_t index) {

    uint32_t seed = internal->last_valuesi[index];
    internal->random_engine.seed(seed);

    internal->last_valuesi[index] = internal->int_channels[index](internal->random_engine);

    return internal->last_valuesi[index];
}
float SeededRNG::use_channelf(uint32_t index) {

    uint32_t seed = internal->float2seed(internal->last_valuesf[index]);
    internal->random_engine.seed(seed);

    internal->last_valuesf[index] = internal->float_channels[index](internal->random_engine);

    return internal->last_valuesi[index];
}
uint32_t SeededRNG::save_channeli(uint32_t index) {
    return internal->last_valuesi[index];
}
void SeededRNG::load_channeli(uint32_t index, uint32_t snapshot) {
    internal->last_valuesi[index] = snapshot;
}
float SeededRNG::save_channelf(uint32_t index) {
    return internal->last_valuesf[index];
}
void SeededRNG::load_channelf(uint32_t index, float snapshot) {
    internal->last_valuesf[index] = snapshot;
}

#ifdef SB_RNG_TEST_CODE
#undef SB_RNG_TEST_CODE
#include <iostream>

int main() {

    SeededRNG testing(50);

    testing.add_channeli(5, 0, 100);

    std::cout << testing.use_channeli(0) << "\n";
    std::cout << testing.use_channeli(0) << "\n";

    std::cout << "Saving...\n";
    uint32_t snapshot = testing.save_channeli(0);

    std::cout << testing.use_channeli(0) << "\n";
    std::cout << testing.use_channeli(0) << "\n";
    std::cout << testing.use_channeli(0) << "\n";
    std::cout << testing.use_channeli(0) << "\n";

    std::cout << "Loading...\n";

    testing.load_channeli(0, snapshot);

    std::cout << testing.use_channeli(0) << "\n";
    std::cout << testing.use_channeli(0) << "\n";
    std::cout << testing.use_channeli(0) << "\n";
    std::cout << testing.use_channeli(0) << "\n";

    testing.add_channeli(15, 0, 100);

    std::cout << "Testing save load with different channels interrupting.\n";

    testing.load_channeli(0, snapshot);

    std::cout << testing.use_channeli(0) << "\n";
    std::cout << testing.use_channeli(0) << "\n\n";

    std::cout << testing.use_channeli(1) << "\n";
    std::cout << testing.use_channeli(1) << "\n";
    std::cout << testing.use_channeli(1) << "\n";
    std::cout << testing.use_channeli(1) << "\n\n";

    std::cout << testing.use_channeli(0) << "\n";
    std::cout << testing.use_channeli(0) << "\n";

}
#endif