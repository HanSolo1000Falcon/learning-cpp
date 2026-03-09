#include "rps_agent.h"

rps_agent::rps_agent(const int difficulty_level) : difficulty_level(difficulty_level) {}

int rps_agent::play(const int user_choice) {
    const int machine_choice = static_cast<int>(associated_rng.next() % (3 + difficulty_level));
    return machine_choice < 3 ? machine_choice : (user_choice + 1) % 3;
}
