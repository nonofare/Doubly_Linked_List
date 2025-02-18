#pragma once
#include <string>

namespace DLL {
    template<typename T>
    class DoubLinList {
        struct Node {
            Node *next;
            Node *prev;
            T data;

            explicit Node(T data) : next(nullptr), prev(nullptr), data(data) {
            }

            ~Node() = default;
        };

        Node *head;
        Node *tail;
        size_t size;

    public:
        DoubLinList() : head(nullptr), tail(nullptr), size(0) {
        }

        ~DoubLinList() {
            erase();
        }

        size_t get_size() const {
            return size;
        }

        void push(T data) {
            push_back(data);
        }

        void push_front(T data) {
            Node *node = new Node(data);

            if (size == 0) {
                head = node;
                tail = node;
            } else {
                head->prev = node;
                node->next = head;
                head = node;
            }
            size++;
        }

        void push_back(T data) {
            Node *node = new Node(data);

            if (size == 0) {
                head = node;
                tail = node;
            } else {
                tail->next = node;
                node->prev = tail;
                tail = node;
            }
            size++;
        }

        bool pop() {
            return pop_front();
        }

        bool pop_front() {
            if (!size) { return false; }

            if (size > 1) {
                Node *temp = head->next;
                delete head;
                head = temp;
                head->prev = nullptr;
                size--;
            } else {
                delete head;
                head = tail = nullptr;
                size--;
            }

            return true;
        }

        bool pop_back() {
            if (!size) { return false; }

            if (size > 1) {
                Node *temp = tail->prev;
                delete tail;
                tail = temp;
                tail->next = nullptr;
                size--;
            } else {
                delete tail;
                head = tail = nullptr;
                size--;
            }

            return true;
        }

        bool remove_specific(T key, bool (*cmp_equal)(T, T) = nullptr) {
            Node *found = find(key, cmp_equal);
            if (!found) { return false; }

            if (found == head) {
                pop_front();
            } else if (found == tail) {
                pop_back();
            } else {
                Node *prev = found->prev;
                Node *next = found->next;
                prev->next = next;
                next->prev = prev;
                delete found;
                size--;
            }

            return true;
        }

        Node *find(T key, bool (*cmp_equal)(T, T) = nullptr) const {
            Node *current = head;

            while (current) {
                if (cmp_equal) {
                    if (cmp_equal(current->data, key)) {
                        return current;
                    }
                } else if constexpr (std::is_arithmetic_v<T>) {
                    if (current->data == key) {
                        return current;
                    }
                }
                current = current->next;
            }

            return nullptr;
        }

        T &operator[](const size_t index) {
            if (index >= size) {
                throw std::out_of_range(
                    "Error: index " + std::to_string(index) + " was not in list range <0," +
                    std::to_string(static_cast<int>(size)) + ")");
            }

            Node *temp = nullptr;
            if (index < size / 2) {
                temp = head;
                for (size_t i = 0; i != index; i++) {
                    temp = temp->next;
                }
            } else {
                temp = tail;
                for (size_t i = size - 1; i != index; i--) {
                    temp = temp->prev;
                }
            }
            return temp->data;
        }

        const T &operator[](const size_t index) const {
            if (index >= size) {
                throw std::out_of_range(
                    "Error: index " + std::to_string(index) + " was not in list range <0," +
                    std::to_string(static_cast<int>(size)) + ")");
            }

            Node *temp = nullptr;
            if (index < size / 2) {
                temp = head;
                for (size_t i = 0; i != index; i++) {
                    temp = temp->next;
                }
            } else {
                temp = tail;
                for (size_t i = size - 1; i != index; i--) {
                    temp = temp->prev;
                }
            }
            return temp->data;
        }

        void erase() {
            while (head) {
                Node *temp = head;
                head = head->next;
                delete temp;
            }
            tail = nullptr;
            size = 0;
        }

        std::string to_str(unsigned int limit = 0, std::string (*fun_str)(T) = nullptr) const {
            if (limit == 0 || limit > size) {
                limit = size;
            }

            std::string text = "Doubly Linked List:\n";
            text += "size: " + std::to_string(static_cast<int>(size)) + "\n";
            text += "{\n";

            Node *temp = head;
            if (fun_str) {
                for (size_t i = 0; i < limit; i++) {
                    text += fun_str(temp->data);
                    text += "\n";
                    temp = temp->next;
                }
            } else if constexpr (std::is_arithmetic_v<T>) {
                for (size_t i = 0; i < limit; i++) {
                    text += std::to_string(temp->data);
                    text += "\n";
                    temp = temp->next;
                }
            } else {
                text = "T was not arithmetic and no function was provided\n";
            }

            if (limit < size) {
                text += "[...]\n";
            }
            text += "}\n";

            return text;
        }
    };
}
