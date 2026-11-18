
#ifndef STACK_H
#define STACK_H
#include "node.hpp"

template <typename T>
class Stack {
private:
    Node<T>* top; // top node pointer
    int count; // number of node

public:
    Stack();
    ~Stack();

    void push(const T& value);
    T pop();
    T peek() const;

    bool isEmpty() const;
    int size() const;
};

#endif
