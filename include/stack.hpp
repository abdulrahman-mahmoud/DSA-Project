#ifndef STACK_H
#define STACK_H

#include <stdexcept>
#include "node.hpp"

template <typename T>
class Stack {
private:
    Node<T>* top;
    int count;

public:
    Stack() : top(nullptr), count(0) {}
    ~Stack() {
        clear();
    }

    // A Stack owns its nodes. Copying would make two stacks share the same
    // chain, so both destructors would delete it.
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    void push(const T& value) {
        top = new Node<T>(value, top);
        ++count;
    }

    T pop() {
        if (isEmpty()) {
            throw std::out_of_range("Stack::pop called on an empty stack");
        }

        Node<T>* oldTop = top;
        T value = oldTop->data;

        top = oldTop->next;
        delete oldTop;
        --count;

        return value;
    }

    T peek() const {
        if (isEmpty()) {
            throw std::out_of_range("Stack::peek called on an empty stack");
        }

        return top->data;
    }

    bool isEmpty() const {
        return top == nullptr;
    }

    int size() const {
        return count;
    }

    void clear() {
        while (top != nullptr) {
            Node<T>* oldTop = top;
            top = top->next;
            delete oldTop;
        }

        count = 0;
    }
};

#endif
