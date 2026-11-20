#ifndef PRIQUEUE_H
#define PRIQUEUE_H

#include <iostream>
#include "node.hpp"
using namespace std;

template <typename T>
class PriQueue {
protected:
    Node<T>* front;
    int count;

public:
    PriQueue() {
        front = nullptr;
        count = 0;
    }   

    virtual ~PriQueue() {
        while (front != nullptr) {
            Node<T>* temp = front;
            front = front->next;
            delete temp;
        }
    }

    virtual bool isHigher(const T& a, const T& b) const{
        return a > b;
    }


    void enqueue(T value) {
        Node<T>* newNode = new Node<T>(value);  
        if (front == nullptr || isHigher(value, front->data)) {
            newNode->next = front;     
            front = newNode;        
        }
      
        else {
            Node<T>* curr = front;

           while (curr->next != nullptr && !isHigher(value, curr->next->data)) {
                curr = curr->next;
            }

            newNode->next = curr->next;
            curr->next = newNode;
        }

        count++;

    }


    bool dequeue(T& value) {

        if (isEmpty()) {

            return false;
        }

        value = front->data;
        Node<T>* temp = front;
        front = front->next;
        delete temp;
        count--;
        return true;
    }


    bool peek(T& value) {



        if (isEmpty()) {

            return false;
        }

        value = front->data;
        return true;
    }

    bool isEmpty() const {
        return count == 0;
    }

    int getCount() const {
        return count;
    }

    void print() const {
        if (isEmpty()) {
            cout << "[ empty ]";
            return;
        }

        Node<T>* curr = front;
        while (curr != nullptr) {
            cout << curr->data << " ";
            curr = curr->next;
        }
        cout << endl;
    }


};

#endif