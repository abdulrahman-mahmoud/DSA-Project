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
    Stack();
    ~Stack();

    void push(const T& value);
    T pop();
    T peek() const;

    bool isEmpty() const;
    int size() const;
};

template <typename T>
Stack<T>::Stack() {
    top = nullptr;
    count = 0;
}

template <typename T>
Stack<T>::~Stack() {
    while (top != nullptr) {
        Node<T>* temp = top;
        top = top->next;
        delete temp;
    }
}

template <typename T>
void Stack<T>::push(const T& value) {
    Node<T>* newNode = new Node<T>(value, top);
    top = newNode;
    count++;
}

template <typename T>
T Stack<T>::pop() {
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

template <typename T>
T Stack<T>::peek() const {
    if (isEmpty()) {
        throw std::out_of_range("Stack is empty");
    }

    return top->data;
}

template <typename T>
bool Stack<T>::isEmpty() const {
    return top == nullptr;
}

template <typename T>
int Stack<T>::size() const {
    return count;
}

#endif
