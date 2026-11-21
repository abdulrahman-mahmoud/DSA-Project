#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include "node.hpp"
using namespace std;

template <typename T>
class Queue {
protected:

    Node<T>* front;
    Node<T>* rear;
    int count;

public:
    Queue() {
        front = nullptr;
        rear  = nullptr;
        count = 0;
    }

    ~Queue() {
        clear();
    }

    void enqueue(T value) {
        Node<T>* newNode = new Node<T>(value);    

        if (rear == nullptr) {
            front = newNode;
            rear  = newNode;
        } else {
            rear->next = newNode;
            rear       = newNode;
        }

        count++;
    }

    bool dequeue(T& value) {
        if (isEmpty()) return false;

        Node<T>* temp = front;
        value      = front->data;
        front      = front->next;

        if (front == nullptr)
            rear = nullptr;

        delete temp;
        count--;
        return true;
    }

    bool peek(T& value) {
        if (isEmpty()) return false;

        value = front->data;
        return true;
    }

    bool isEmpty() const {
        return count == 0;
    }

    int getCount() const {
        return count;
    }

    void clear() {
        while (front != nullptr) {
            Node<T>* temp = front;
            front = front->next;
            delete temp;
        }
        rear  = nullptr;
        count = 0;
    }

    void print() const {
        if (isEmpty()) {
            cout << " [ empty ]" << endl;
            return;
        }

        Node<T>* current = front;
        while (current != nullptr) {
            cout << current->data;
            if (current->next != nullptr) {
                cout << "      ---------------------------------\n";
            }
            current = current->next;
        }
        cout << endl;
    }
};

#endif
