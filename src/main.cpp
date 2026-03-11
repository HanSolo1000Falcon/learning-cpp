#include "linked-list/list.hpp"
#include "ttt/tictactoe_manager.hpp"

void print_list(list &list) {
    std::cout << "List: (size " << list.size() << ") ";
    for (const auto &value : list) {
        std::cout << *static_cast<int *>(value) << " ";
    }
    std::cout << std::endl;
}

int main() {
    auto l_list = list();

    auto df1 = static_cast<int *>(malloc(sizeof(int)));
    auto df2 = static_cast<int *>(malloc(sizeof(int)));
    auto df3 = static_cast<int *>(malloc(sizeof(int)));

    *df1 = 1;
    *df2 = 2;
    *df3 = 3;

    l_list.push_back(df1);
    l_list.push_back(df2);
    l_list.push_back(df3);
    l_list.push_back(df1);
    l_list.push_back(df2);
    l_list.push_back(df3);
    l_list.push_back(df1);
    l_list.push_back(df2);
    l_list.push_back(df3);
    print_list(l_list);
    l_list.remove_all_occurences_of(df3);
    print_list(l_list);
    l_list.remove_first_occurence_of(df1);
    print_list(l_list);
    l_list.remove_last_occurence_of(df2);
    print_list(l_list);
    l_list.remove_at(0);
    print_list(l_list);

    return 0;
}
