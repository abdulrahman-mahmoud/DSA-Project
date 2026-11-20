#ifndef ORGANIZER_H
#define ORGANIZER_H

#include <iostream>
#include "queue.hpp"
#include "request.hpp"
#include "locations.hpp"

using namespace std;

class Organizer {
private:
    Queue<Request*> WaitingSR;
    Queue<Request*> CancelRequests;
    Queue<Request*> CompletedTickets; 

    Queue<Request*> WaitingNR;
    Queue<Request*> WaitingUR;

    // Simulation tracking
    int totalTickets;
    int finishedCount;
    int cancelledCount;
    int tick;

    // added by hassan for organizer loader
    Locations* locations;

public:
    Organizer();
    ~Organizer();

    void addRequest(Request* req);
    void loadSampleData();
    void simulate();
    void printState() const;

    // organizer loader function added by hassan
    bool loadInputFile(const string& filename);
};

#endif
