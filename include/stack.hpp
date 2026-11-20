#ifndef STACK_H
#define STACK_H

#include "node.hpp"
#include <stdexcept>

template <typename T>
class Stack {
private:
    Node<T>* top;
    int count;

public:
    Stack() {
        top = nullptr;
        count = 0;
    }

    ~Stack() {
        while (top != nullptr) {
            Node<T>* temp = top;
            top = top->next;
            delete temp;
        }
    }

    void push(const T& value) {
        Node<T>* newNode = new Node<T>(value, top);
        top = newNode;
        count++;
    }

    T pop() {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }

        Node<T>* temp = top;
        T value = top->data;

        top = top->next;
        delete temp;
        count--;

        return value;
    }

    T peek() const {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }

        return top->data;
    }

    bool isEmpty() const {
        return top == nullptr;
    }

    int size() const {
        return count;
    }
};

#endif