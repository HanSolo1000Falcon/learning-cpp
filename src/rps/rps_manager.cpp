#include "rps_manager.h"

#include <algorithm>
#include <iostream>
#include <ostream>

#include "rps_agent.h"

std::string to_lower_variant(std::string &str) {
    std::ranges::transform(str, str.begin(), ::tolower);
    return str;
}

void rps_manager::init_game_and_start_game_loop() {
    std::cout << "Game started!" << std::endl;

    while (true) {
        auto game_over = false;

        int difficulty_level;
        std::cout << "Please pick a difficulty level (0-Infinity): ";
        std::cin >> difficulty_level;

        if (difficulty_level < 0) {
            std::cout << "Difficulty level must be greater than or equal to 0." << std::endl;
            continue;
        }

        auto agent = rps_agent(difficulty_level);

        while (true) {
            std::string user_choice;
            std::cout << std::endl;
            std::cout << "Please pick a move (rock, paper, scissors)" << std::endl;
            std::cin >> user_choice;
            to_lower_variant(user_choice);

            if (user_choice != "rock" && user_choice != "paper" && user_choice != "scissors") {
                std::cout << "Invalid choice." << std::endl;
                continue;
            }

            const int machine_choice = agent.play(user_choice == "rock" ? 0 : user_choice == "paper" ? 1 : 2);
            std::cout << "The machine chose " << (machine_choice == 0 ? "rock" : (machine_choice == 1 ? "paper" : "scissors")) << "." << std::endl;

            int chosen_continuation;
            std::cout << "Please pick one:\n1. Continue playing.\n2. Change difficulty level.\n3. End game." << std::endl;
            std::cin >> chosen_continuation;

            auto should_break = false;
            switch (chosen_continuation) {
                case 1:
                    continue;

                case 2:
                    should_break = true;
                    break;

                case 3:
                    should_break = true;
                    game_over = true;
                    break;

                default:
                    std::cout << "Invalid choice. Continuing play..." << std::endl;
                    break;
            }

            if (should_break) {
                break;
            }
        }

        if (game_over) {
            break;
        }
    }
}