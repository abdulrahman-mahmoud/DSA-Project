#include "../include/node.hpp"
#include "../include/Technician.hpp"
#include "../include/FreeTechnicianList.hpp"

FreeTechnicianList::FreeTechnicianList(){
    front = nullptr;
    count = 0;
}
int FreeTechnicianList::getCount()const{
    return count;
}
bool FreeTechnicianList::isEmpty()const{
    return front == nullptr;
}

void FreeTechnicianList::insert(Technician* technician) { // sorted linked list

    Node<Technician*>* temp = new Node<Technician*>(technician);

    Node<Technician*>* prev = nullptr;
    Node<Technician*>* curr = front;

    if (front == nullptr || technician->getID() < front->data->getID()) { // inserting the code
        temp->next = front;
        front = temp;
        count++;
        return;
    }

    while (curr != nullptr && curr->data->getID() <= technician->getID()) { // sorting the data 
        prev = curr;
        curr = curr->next;
    }

    temp->next = curr;
    prev->next = temp;

    count++;
    
}
Technician* FreeTechnicianList::remove() { 
    if (front == nullptr) {
        return nullptr;
    }

    Node<Technician*>* temp = front;
    Technician* technician = temp->data;
    front = front->next;
    delete temp;
    --count;

    return technician;
}

void FreeTechnicianList::print() const {
    Node<Technician*>* curr = front;

    while (curr != nullptr) {
        cout << curr->data->getID() << endl;
        curr = curr->next;
    }
}

FreeTechnicianList::~FreeTechnicianList() {
    Node<Technician*>* curr = front;

    while (curr != nullptr) {
        Node<Technician*>* temp = curr;
        curr = curr->next;
        delete temp;
    }

    front = nullptr;
    count = 0;
}