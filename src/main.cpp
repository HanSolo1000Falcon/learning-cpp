#include "ttt/tictactoe_board.hpp"

tictactoe_coordinate parse_coordinate(const std::string &coordinate_string) {
    const auto comma = coordinate_string.find(',');
    if (comma == std::string::npos) {
        throw std::invalid_argument("missing comma");
    }
    return {std::stoi(coordinate_string.substr(0, comma)), std::stoi(coordinate_string.substr(comma + 1))};
}

int main() {
    auto ttt_board = tictactoe_board();
    auto was_x = false;
    while (true) {
        was_x = !was_x;
        ttt_board.draw_board();
        std::cout << "\nPlease enter your move (x,y): ";

        tictactoe_coordinate coordinate{};
        bool valid = false;
        while (!valid) {
            std::string move;
            std::cin >> move;
            try {
                coordinate = parse_coordinate(move);

                if (coordinate.x > tictactoe_board::board_size - 1 || coordinate.y > tictactoe_board::board_size - 1 ||
                    ttt_board.is_occupied(coordinate) || coordinate.x < 0 || coordinate.y < 0) {
                    std::cout << "Invalid coordinate, try again (x,y): ";
                    continue;
                }

                valid = true;
            } catch (const std::invalid_argument &e) {
                std::cout << "Bad input, try again (x,y): ";
            }
        }

        ttt_board.play_move(coordinate, was_x);
    }
    return 0;
}
