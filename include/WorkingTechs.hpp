#ifndef WORKINGTECHS_H
#define WORKINGTECHS_H

#include "PriQueue.hpp"
#include "Technician.hpp"

class WorkingTechs : public PriQueue<Technician*> {
public:

    bool isHigher(Technician* const& a, Technician* const& b) const override {
        // Phase 1 technicians may have no assigned ticket (nullptr).
        Request* reqA = (a != nullptr) ? a->getCurrentRequest() : nullptr;
        Request* reqB = (b != nullptr) ? b->getCurrentRequest() : nullptr;

        if (reqA == nullptr && reqB == nullptr) {
            if (a != nullptr && b != nullptr) return a->getID() < b->getID();
            return false;
        }
        if (reqA == nullptr) return false;
        if (reqB == nullptr) return true;

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