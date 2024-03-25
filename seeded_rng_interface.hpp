#ifndef SB_SEEDED_RNG
#define SB_SEEDED_RNG

#include <stdint.h>

struct RNG_INTERNAL;

// Spencer Banasik - 3/25/2024
// This class aims to provide pseudo-random number generation, and a method to save and load states of that RNG at will.
// You may add multiple channels, configure them as needed, and use either floats or integers.
// One caveat of floats is that the rng may be lackluster for precise values and end up generating similar vlaues.
// Because of this, I'd personally recommend generating an integer and processing that into the data needed.
// Additionally, since the loading is just a number, it's possible to arbitrarily set the RNG to certain values without saving.
// Things that would be nice:
// - Saving and loading all channels, this would require me to either #include vector/array or to return a dynamic array that the user would
// need to remove.
// - A better method of converting floats to integers.
// Things outside of scope:
// - Providing names for channel access, the user can choose to add an associative map, constants, or an enum
// - Allowing for nonsequential addition and removal
class SeededRNG {
public:

    SeededRNG(uint32_t seed);
    ~SeededRNG();

    // Add an int channel to RNG, takes in a seed for channel, and then the minimum and maximum.
    void add_channeli(uint32_t rand_val, uint32_t minimum, uint32_t maximum);
    // Add a float channel to RNG
    void add_channelf(uint32_t rand_val, float minimum, float maximum);
    // Config channel for integers, clamps index
    void config_channeli(uint32_t index, uint32_t minimum, uint32_t maximum);
    // Config channel for floats, clamps intdex
    void config_channelf(uint32_t index, float minimum, float maximum);

    // Remove a channel from our RNG, clamps index, indexes on the right are shifted down
    void remove_channeli(uint32_t index);
    // Remove a channel from our RNG, clamps index, indexes on the right are shifted down
    void remove_channelf(uint32_t index);

    // Returns the size, elems are sequential
    uint32_t get_num_channelsi();
    // Returns the size, elems are sequential
    uint32_t get_num_channelsf();

    // Returns an int from a channel
    uint32_t use_channeli(uint32_t index);
    // Returns a float from a channel
    float use_channelf(uint32_t index);

    // Saves an integer channel state
    uint32_t save_channeli(uint32_t index);
    // Loads an integer channel state
    void load_channeli(uint32_t index, uint32_t snapshot);

    // Saves a float channel state
    float save_channelf(uint32_t index);
    // Loads a float channel state
    void load_channelf(uint32_t index, float snapshot);

private:

    RNG_INTERNAL* internal;

};
#endif