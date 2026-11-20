#include "../include/FreeTechnicianList.hpp"

// this code for freeST/freeGT

bool FreeTechnicianList::isHigher(Technician* const& a, Technician* const& b) const {
    if (a == nullptr) {
        return false;
    }

    if (b == nullptr) {
        return true;
    }

    return a->getID() < b->getID();
}

void FreeTechnicianList::insert(Technician* technician) {
    if (technician != nullptr) {
        enqueue(technician);
    }
}

Technician* FreeTechnicianList::remove() {
    Technician* technician = nullptr;

    if (dequeue(technician)) {
        return technician;
    }

    return nullptr;
}

void FreeTechnicianList::print() const {
    if (isEmpty()) {
        cout << "empty" << endl;
        return;
    }

    Node<Technician*>* current = front;
    while (current != nullptr) {
        if (current->data != nullptr) {
            cout << current->data->getID() << " ";
        } else {
            cout << "null ";
        }
        current = current->next;
    }
    cout << endl;
}