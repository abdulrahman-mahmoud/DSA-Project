
#include "../include/stack.hpp"

template <typename T>
Stack<T>::Stack() { // stack constructor
    top = nullptr;
    count = 0;
}

template <typename T>
Stack<T>::~Stack() { // stack destructor (delete all nodes from top to bottom)
    while (top != nullptr) {
        Node* temp = top;
        top = top->next;
        delete temp;
    }
}

template <typename T>
void Stack<T>::push(const T& value) { // push to stack
    Node* newNode = new Node(value, top); // constructor runs and new node points to top

    top = newNode;
    count++;
}

template <typename T>
T Stack<T>::pop() {
    if (isEmpty()) {
        throw std::out_of_range("Stack is empty");
    }

    Node* temp = top;
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

    value = top->data;
    return value;
}

template <typename T>
bool Stack<T>::isEmpty() const {
    return top == nullptr;
}

template <typename T>
int Stack<T>::size() const {
    return count;
}
