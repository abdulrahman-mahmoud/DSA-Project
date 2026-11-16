
#ifndef STACK_H
#define STACK_H

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;

        Node(const T& value, Node* nextNode)
            : data(value), next(nextNode) {} // constructor
    };

    Node* top; // top node pointer
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
