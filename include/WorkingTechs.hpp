#ifndef WORKINGTECHS_H
#define WORKINGTECHS_H

#include "PriQueue.hpp"
#include "Technician.hpp"

class WorkingTechs : public PriQueue<Technician*> {
public:

    bool isHigher(Technician* const& a, Technician* const& b) const override {

        Request* reqA = a->getCurrentRequest();
        Request* reqB = b->getCurrentRequest();

        if (reqA->getFT() != reqB->getFT())
            return reqA->getFT() < reqB->getFT();

        return reqA->getRID() < reqB->getRID();
    }

    void print() const {
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
};

#endif