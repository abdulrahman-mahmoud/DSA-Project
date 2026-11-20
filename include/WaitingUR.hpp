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

        // RULE 2: same PR, different QT -> the earlier (smaller) QT goes first
        if (a->getQT() != b->getQT()) {
            return a->getQT() < b->getQT();
        }

        // RULE 3: same PR and same QT -> the smaller RID goes first
        return a->getRID() < b->getRID();
    }
};

#endif