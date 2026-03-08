#include "rng.h"

#include <ctime>

rng::rng() : seed(time(nullptr) << 3) {}
rng::rng(const unsigned long long custom_seed) : seed(custom_seed) {}

unsigned long long rng::next() {
    const auto last_value = current();
    const auto step_one = seed * last_value;
    const auto step_two = step_one << 2;
    const auto step_three = step_two ^ last_value;
    const auto step_four = step_three >> 2;
    const auto result = step_four * last_value / 100;
    generated_values.push_back(result);
    return result;
}

unsigned long long rng::get_seed() const { return seed; }

unsigned long long rng::current() const {
    return generated_values.empty() ? seed : generated_values.at(generated_values.size() - 1);
}

unsigned long long rng::at(const size_t index) const { return generated_values.at(index); }

size_t rng::size() const { return generated_values.size(); }
