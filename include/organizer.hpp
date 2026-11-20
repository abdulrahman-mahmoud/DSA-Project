#ifndef ORGANIZER_H
#define ORGANIZER_H

#include <iostream>
#include "queue.hpp"
#include "request.hpp"
#include "locations.hpp"
#include "WaitingNR.hpp"
#include "WaitingSR.hpp"
#include "WaitingUR.hpp"
#include "ITUnit.hpp"
#include "WorkingTechs.hpp"

using namespace std;

class Organizer {
private:
    WaitingSR waitingSR;
    Queue<Request*> CancelRequests;
    Queue<Request*> CompletedTickets; 

    WaitingNR waitingNR;
    WaitingUR waitingUR;

    ITUnit* itUnit;
    WorkingTechs workingTechs;

    // Simulation tracking
    int totalTickets;
    int finishedCount;
    int cancelledCount;
    int tick;

    // added by hassan for organizer loader
    Locations* locations;
    int* serviceDuration;
    int problemCount;

public:
    Organizer();
    ~Organizer();

    void addRequest(Request* req);
    void loadSampleData();
    void simulate(bool interactive = false);
    void printState() const;

    // organizer loader function added by hassan
    bool loadInputFile(const string& filename);
};

#endif
