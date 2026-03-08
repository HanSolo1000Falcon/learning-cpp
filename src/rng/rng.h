#ifndef LEARNING_PROJECTS_RNG_H
#define LEARNING_PROJECTS_RNG_H
#include <vector>

class rng {
    const unsigned long long seed;
    std::vector<unsigned long long> generated_values = std::vector<unsigned long long>();

public:
    rng();
    explicit rng(unsigned long long custom_seed);

    unsigned long long next();

    [[nodiscard]] unsigned long long get_seed() const;
    [[nodiscard]] unsigned long long current() const;
    [[nodiscard]] unsigned long long at(size_t index) const;
    [[nodiscard]] size_t size() const;
};

#endif // LEARNING_PROJECTS_RNG_H
