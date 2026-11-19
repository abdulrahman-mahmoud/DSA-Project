#ifndef WAITING_NR
#define WAITING_NR

#include "include/Queue.hpp"
#include "include/request.hpp"

class WaitingNR : public Queue<Request*> {
    public:
        Request* cancelByRID(int rid);
};

#endif