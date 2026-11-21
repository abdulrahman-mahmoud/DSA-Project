#ifndef WAITINGSR_H
#define WAITINGSR_H

#include "Queue.hpp"
#include "request.hpp"

class WaitingSR : public Queue<Request*> {
public:
    WaitingSR() : Queue<Request*>() {}

    ~WaitingSR() {}

};

#endif
