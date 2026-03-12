/*
 * Took some inspiration from C#'s `List<T>`
 * Still like an `std::vector<typename T>` but actually somewhat usable.
 */

#ifndef LEARNING_PROJECTS_L_LIST_HPP
#define LEARNING_PROJECTS_L_LIST_HPP
#include <stdexcept>

template<typename T>
class l_list {
    struct node {
        T *data = nullptr;
        node *next;
        node *previous;

        ~node() {
                delete data;
        }
    };

    struct node_iterator {
        node *current;

        node_iterator(node *current) : current(current) {}

        T operator*() const { return *(current->data); }
        bool operator!=(const node_iterator &other) const { return current != other.current; }

        node_iterator &operator++() {
            current = current->next;
            return *this;
        }

        node_iterator &operator--() {
            current = current->previous;
            return *this;
        }
    };

    node *sentry;

    node *get_node_internal(int index) {
        if (index >= size() || index < 0) {
            throw std::out_of_range("Specified index is out of range.");
        }

        auto current = sentry->next;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current;
    }

public:

    l_list() {
        sentry = new node();
        sentry->next = sentry;
        sentry->previous = sentry;
    }

    ~l_list() {
        auto current = sentry->next;
        while (current != sentry) {
            auto next = current->next;
            delete current;
            current = next;
        }
    }

    void add(T data) {
        T *data_pointer = new T();
        *data_pointer = data;

        const auto new_node = new node();
        new_node->data = data_pointer;
        sentry->previous->next = new_node;
        new_node->previous = sentry->previous;
        new_node->next = sentry;
        sentry->previous = new_node;
    }

    void remove_first(T data) {
        for (auto it = begin(); it != end(); ++it) {
            node *current = it.current;
            if (*(current->data) == data) {
                current->previous->next = current->next;
                current->next->previous = current->previous;
                delete current;
                return;
            }
        }
    }

    void remove_last(T data) {
        auto it = rbegin();
        while (it != rend()) {
            node *current = it.current;
            ++it;
            if (*(current->data) == data) {
                current->previous->next = current->next;
                current->next->previous = current->previous;
                delete current;
                return;
            }
        }
    }

    void remove_all(T data) {
        auto it = rbegin();
        while (it != rend()) {
            node *current = it.current;
            ++it;
            if (*(current->data) == data) {
                current->previous->next = current->next;
                current->next->previous = current->previous;
                delete current;
            }
        }
    }

    void remove_at(const int index) {
        if (index >= size() || index < 0) {
            throw std::out_of_range("Specified index is out of range.");
        }
        auto to_delete = get_node_internal(index);
        auto previous = to_delete->previous;
        auto next = to_delete->next;
        previous->next = next;
        next->previous = previous;
        delete to_delete;
    }

    T find_first(T data) {
        for (T foo_data : *this) {
            if (foo_data == data) {
                return foo_data;
            }
        }
        throw std::out_of_range("Specified data was not found.");
    }

    T find_last(T data) {
        for (auto it = rbegin(); it != rend(); --it) {
            if (*it == data) {
                return *it;
            }
        }
        throw std::out_of_range("Specified data was not found.");
    }

    l_list find_all(T data) {
        l_list found_list;
        for (T foo_data : *this) {
            if (foo_data == data) {
                found_list.add(foo_data);
            }
        }
        return found_list;
    }

    T operator[](int index) {
        if (index >= size() || index < 0) {
            throw std::out_of_range("Specified index is out of range.");
        }

        for (T data : *this) {
            if (index == 0) {
                return data;
            }
            --index;
        }

        throw std::out_of_range("Specified index is out of range.");
    }

    size_t size() {
        size_t size = 0;
        for (T data : *this) {
            ++size;
        }
        return size;
    }

    [[nodiscard]] node_iterator begin() const { return {sentry->next}; }
    [[nodiscard]] node_iterator end() const { return {sentry}; }
    [[nodiscard]] node_iterator rbegin() const { return node_iterator(sentry->previous); }
    [[nodiscard]] node_iterator rend() const { return node_iterator(sentry); }
};

#endif // LEARNING_PROJECTS_L_LIST_HPP
