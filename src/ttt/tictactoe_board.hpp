#ifndef LEARNING_PROJECTS_TICTACTOE_BOARD_HPP
#define LEARNING_PROJECTS_TICTACTOE_BOARD_HPP
#include <algorithm>
#include <iostream>
#include <ostream>
#include <vector>

struct tictactoe_coordinate {
    int x;
    int y;

    bool operator==(const tictactoe_coordinate &other) const {
        return x == other.x && y == other.y;
    }
};

inline bool vector_contains(const std::vector<tictactoe_coordinate> &vector, const tictactoe_coordinate element) {
    const int place = std::ranges::count(vector.begin(), vector.end(), element);
    return place > 0;
}

class tictactoe_board {
    std::vector<tictactoe_coordinate> free_cells = std::vector<tictactoe_coordinate>();
    std::vector<tictactoe_coordinate> x_occupied_cells = std::vector<tictactoe_coordinate>();
    std::vector<tictactoe_coordinate> o_occupied_cells = std::vector<tictactoe_coordinate>();

public:
    constexpr static int board_size = 3;

    explicit tictactoe_board() {
        for (int x = 0; x < board_size; x++) {
            for (int y = 0; y < board_size; y++) {
                free_cells.push_back({x, y});
            }
        }
    }

    void draw_board() const {
        for (auto y = 0; y < board_size; ++y) {
            for (auto x = 0; x < board_size; ++x) {
                const tictactoe_coordinate coordinate = {x, y};
                if (x > 0) {
                    std::cout << "|";
                }
                std::cout << " " << (vector_contains(x_occupied_cells, coordinate) ? "X" : vector_contains(o_occupied_cells, coordinate) ? "O" : " ") << " ";
            }
            std::cout << "\n";
            if (y < board_size - 1) {
                std::cout << "---|---|---\n";
            }
        }
    }

    void play_move(const tictactoe_coordinate &coordinate, const bool is_x) {
        if (vector_contains(free_cells, coordinate)) {
            free_cells.erase(std::ranges::find(free_cells, coordinate));
            if (is_x) {
                x_occupied_cells.push_back(coordinate);
            } else {
                o_occupied_cells.push_back(coordinate);
            }
        } else {
            std::cout << "Already occupied, try again." << std::endl;
        }
    }

    [[nodiscard]] bool is_occupied(const tictactoe_coordinate &coordinate) const {
        return !vector_contains(free_cells, coordinate);
    }
};

#endif // LEARNING_PROJECTS_TICTACTOE_BOARD_HPP
