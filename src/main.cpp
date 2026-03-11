#include "bitmap-visualizer/bv_manager.hpp"

int main() {
    auto bv = bv_manager();
    bv.render_bitmap();
    return 0;
}
