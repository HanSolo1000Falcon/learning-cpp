#ifndef LEARNING_PROJECTS_BITMAP_HPP
#define LEARNING_PROJECTS_BITMAP_HPP
#include <bitset>
#include <format>
#include <iostream>

class bitmap {
    const int *underlying_data;

    explicit bitmap(const int *underlying_data) : underlying_data(underlying_data) { }

public:
    /**
     * Creates a new instance of the `bitmap` class using the provided data.
     *
     * @param data A pointer to an integer representing the underlying data for the bitmap.
     *             This value must not be null.
     * @return A pointer to a newly created `bitmap` instance if the input data is valid.
     *         Returns `nullptr` if the input data is null.
     */
    static bitmap *create(const int *data) {
        if (data == nullptr) {
            std::cout << "Error when creating bitmap, data cannot be null" << std::endl;
            return nullptr;
        }

        const auto created = new bitmap(data);
        return created;
    }

    [[nodiscard]] std::string render() const {
        std::string rendered = std::format("{:p} ({:d}) ->\n", static_cast<const void *>(underlying_data), *underlying_data);
        const auto bitset = std::bitset<sizeof(int) * 8>(*underlying_data);
        for (int y = 0; y < 8; ++y) {
            for (int x = 0; x < 8; ++x) {
                if (x == 0) {
                    rendered += "|";
                }
                rendered += bitset[31 - (y * 8 + x)] ? "X" : " ";
                rendered += "|";
            }
            rendered += "\n";
        }
        rendered += std::format("{:032b}", *underlying_data);
        return rendered;
    }
};

#endif // LEARNING_PROJECTS_BITMAP_HPP
