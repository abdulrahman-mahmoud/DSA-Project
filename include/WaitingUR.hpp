#ifndef WAITINGUR_H
#define WAITINGUR_H

#include "PriQueue.hpp"
#include "request.hpp"

class WaitingUR : public PriQueue<Request*> {
public:

    bool isHigher(Request* const& a, Request* const& b) const override {

        if (a->getPR() != b->getPR()) {
            return a->getPR() > b->getPR();
        }

        
        if (a->getQT() != b->getQT()) {
            return a->getQT() < b->getQT();
        }

        
        return a->getRID() < b->getRID();
    }
};

#endif
