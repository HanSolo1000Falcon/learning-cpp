#ifndef LEARNING_PROJECTS_RPS_AGENT_H
#define LEARNING_PROJECTS_RPS_AGENT_H
#include "../rng/rng.h"


class rps_agent {
    const int difficulty_level;
    rng associated_rng = rng();

public:
    explicit rps_agent(int difficulty_level);
    int play(int user_choice);
};


#endif // LEARNING_PROJECTS_RPS_AGENT_H
