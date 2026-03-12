#include <iostream>
#include <ostream>

#include "linked-list/l_list.hpp"

template<typename T>
void print_list(const l_list<T> &list) {
    for (const T i: list) {
        std::cout << i;
    }
    std::cout << std::endl;
}

int main() {
    auto int_list = l_list<int>();
    for (int i = 0; i < 10; ++i) {
        int_list.add(1);
        int_list.add(2);
        int_list.add(3);
        int_list.add(4);
        int_list.add(5);
    }
    print_list(int_list);
    int_list.remove_first(2);
    print_list(int_list);
    int_list.remove_last(5);
    print_list(int_list);
    int_list.remove_all(3);
    print_list(int_list);
    int_list.remove_at(2);
    print_list(int_list);
    std::cout << int_list.find_first(2) << std::endl;
    std::cout << int_list.find_last(2) << std::endl;
    print_list(int_list.find_all(2));
    return 0;
}
