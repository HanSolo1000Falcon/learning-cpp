#ifndef LEARNING_PROJECTS_BV_MANAGER_HPP
#define LEARNING_PROJECTS_BV_MANAGER_HPP
#include "../rng/rng.h"
#include "bitmap.hpp"

class bv_manager {
    int *underlying_data;
    bitmap *underlying_bitmap;
    rng *local_rng;

public:
    bv_manager() {
        underlying_data = static_cast<int *>(malloc(sizeof(int)));
        underlying_bitmap = bitmap::create(underlying_data);
        local_rng = new rng();
    }

    void render_bitmap() const {
        *underlying_data = static_cast<int>(local_rng->next());
        std::cout << underlying_bitmap->render() << std::endl;
    }
};

#endif // LEARNING_PROJECTS_BV_MANAGER_HPP
