/*
 * Almost like `std::vector<T>` but horribly coded!
 * It's just a linked list...
 */

#ifndef LEARNING_PROJECTS_LIST_HPP
#define LEARNING_PROJECTS_LIST_HPP
#include <stdexcept>

class list {
    struct node {
        void *data;

        node *next;
        node *previous;
    };

    struct node_iterator {
        node *current;

        node_iterator(node *current) : current(current) {}

        void *operator*() const { return current->data; }
        node_iterator &operator++() { current = current->next; return *this; }
        bool operator!=(const node_iterator &other) const { return current != other.current; }
    };

    node *tail;

    node *create_node_internal() {
        const auto new_node = new node();
        new_node->next = nullptr;
        new_node->previous = nullptr;
        new_node->data = nullptr;
        return new_node;
    }

    void remove_and_unlink_node_internal(node *node) {
        node->previous->next = node->next;
        node->next->previous = node->previous;
        delete node;
    }

    node *get_at_internal(size_t index) {
        if (index >= size() || index < 0) {
            throw std::out_of_range("Specified index is out of range.");
        }

        auto current = tail->next;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current;
    }

public:
    list() {
        tail = create_node_internal();
        tail->next = tail;
        tail->previous = tail;
    }

    ~list() {
        const node *current = tail->next;
        while (current != tail) {
            const node *next = current->next;
            delete current;
            current = next;
        }
    }

    void push_back(void *data) {
        const auto new_node = create_node_internal();
        new_node->data = data;
        tail->previous->next = new_node;
        new_node->previous = tail->previous;
        new_node->next = tail;
        tail->previous = new_node;
    }

    void remove_first_occurence_of(void *data) {
        if (const auto index = find_first_occurence_of(data); index != -1) {
            remove_at(index);
        }
    }

    void remove_last_occurence_of(void *data) {
        if (const auto index = find_last_occurence_of(data); index != -1) {
            remove_at(index);
        }
    }

    void remove_all_occurences_of(void *data) {
        list indices;
        size_t index = 0;
        for (auto this_data : *this) {
            if (this_data == data) {
                auto* idx = new size_t(index);
                indices.push_back(idx);
            }
            ++index;
        }

        for (int i = indices.size() - 1; i >= 0; --i) {
            size_t actual_index = *static_cast<size_t*>(indices.at(i));
            delete static_cast<size_t*>(indices.at(i));
            remove_at(actual_index);
        }
    }

    void remove_at(size_t index) {
        node *to_remove = get_at_internal(index);
        remove_and_unlink_node_internal(to_remove);
    }

    size_t find_first_occurence_of(const void *data) const {
        auto current = tail->next;
        size_t index = 0;
        while (current != tail) {
            if (current->data == data) {
                return index;
            }
            current = current->next;
            ++index;
        }
        return -1;
    }

    size_t find_last_occurence_of(const void *data) {
        auto current = tail->previous;
        size_t index = size() - 1;
        while (current != tail) {
            if (current->data == data) {
                return index;
            }
            current = current->previous;
            --index;
        }
    }

    list get_all_occurences_of(const void *data) {
        auto occurences = list();
        size_t index = 0;
        for (auto this_data : *this) {
            if (this_data == data) {
                occurences.push_back(&index);
            }
            ++index;
        }
        return occurences;
    }

    void *at(size_t index) {
        return get_at_internal(index)->data;
    }

    size_t size() {
        size_t size = 0;
        for (auto data : *this) {
            ++size;
        }
        return size;
    }

    [[nodiscard]] node_iterator begin() const { return {tail->next}; }
    node_iterator end() { return {tail}; }
};

#endif // LEARNING_PROJECTS_LIST_HPP
