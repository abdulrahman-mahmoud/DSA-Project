#include "../include/organizer.hpp"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

Organizer::Organizer() {
    totalTickets   = 0;
    finishedCount  = 0;
    cancelledCount = 0;
    tick       = 0;
    srand(0);
}

Organizer::~Organizer() {
    Request* req = nullptr;
    while (WaitingSR.dequeue(req))        { delete req; }
    while (WaitingNR.dequeue(req))        { delete req; }
    while (WaitingUR.dequeue(req))        { delete req; }
    while (CompletedTickets.dequeue(req)) { delete req; }
    while (CancelRequests.dequeue(req))   { delete req; }
}

void Organizer::addRequest(Request* req) {
    if (req == nullptr) return;

    if (req->getType() == SR) {
        WaitingSR.enqueue(req);
    } else if (req->getType() == UR) {
        WaitingUR.enqueue(req);
    } else {
        WaitingNR.enqueue(req);
    }
    totalTickets++;
}

void Organizer::loadSampleData() {
    addRequest(new Request(101, 1, 1, 10, SR, 0));
    addRequest(new Request(102, 1, 2, 15, NR, 0));
    addRequest(new Request(103, 2, 1, 20, UR, 3));
    addRequest(new Request(104, 2, 3, 25, SR, 0));
    addRequest(new Request(105, 3, 2, 10, NR, 0));
}

void Organizer::printState() const {
    cout << "           [Step " << tick << "]\n";
    cout << "WaitingSR (" << const_cast<Queue<Request*>&>(WaitingSR).getCount() << "): ";
    const_cast<Queue<Request*>&>(WaitingSR).print();

    cout << "Completed (" << const_cast<Queue<Request*>&>(CompletedTickets).getCount() << "): ";
    const_cast<Queue<Request*>&>(CompletedTickets).print();

    cout << "Cancelled (" << const_cast<Queue<Request*>&>(CancelRequests).getCount() << "): ";
    const_cast<Queue<Request*>&>(CancelRequests).print();

    cout << "Progress: Finished=" << finishedCount 
         << " + Cancelled=" << cancelledCount 
         << " = " << (finishedCount + cancelledCount) 
         << " / " << totalTickets << "\n\n";
}

void Organizer::simulate() {
    cout << "       Starting Simulation (Total: " << totalTickets << " Tickets) \n\n";
    printState();

    // Loop runs until: Finished + Cancelled == totalTickets
    while (finishedCount + cancelledCount < totalTickets) {
        tick++;

        int r = (rand() % 100) + 1;

        if (r <= 25) {
            //SR Ticket finish
            if (!WaitingSR.isEmpty()) {
                Request* req = nullptr;
                WaitingSR.dequeue(req);
                req->setStatus(COMPLETED);
                req->setFT(tick);
                CompletedTickets.enqueue(req);
                finishedCount++;
                cout << ">> Move 1 (r=" << r << "): SR #" << req->getRID() << " completed.\n";
            } else {
                cout << ">> Move 1 (r=" << r << "): WaitingSR empty.\n";
            }
        }
        else if (r <= 45) {
            //NR Ticket finish 
            if (!WaitingNR.isEmpty()) {
                Request* req = nullptr;
                WaitingNR.dequeue(req);
                req->setStatus(COMPLETED);
                req->setFT(tick);
                CompletedTickets.enqueue(req);
                finishedCount++;
                cout << ">> Move 2 (r=" << r << "): NR #" << req->getRID() << " completed.\n";
            } else {
                cout << ">> Move 2 (r=" << r << "): WaitingNR empty.\n";
            }
        }
        else if (r <= 60) {
            //UR Ticket finish
            if (!WaitingUR.isEmpty()) {
                Request* req = nullptr;
                WaitingUR.dequeue(req);
                req->setStatus(COMPLETED);
                req->setFT(tick);
                CompletedTickets.enqueue(req);
                finishedCount++;
                cout << ">> Move 3 (r=" << r << "): UR #" << req->getRID() << " completed.\n";
            } else {
                cout << ">> Move 3 (r=" << r << "): WaitingUR empty.\n";
            }
        }
        else if (r <= 75) {
            //NR Ticket cancelled
            if (!WaitingNR.isEmpty()) {
                Request* req = nullptr;
                WaitingNR.dequeue(req);
                req->setStatus(CANCELLED);
                CancelRequests.enqueue(req);
                cancelledCount++;
                cout << ">> Move 4 (r=" << r << "): NR #" << req->getRID() << " cancelled.\n";
            } else {
                cout << ">> Move 4 (r=" << r << "): WaitingNR empty (no cancel).\n";
            }
        }
        else if (r <= 85) {
            // SR ticket finishes
            if (!WaitingSR.isEmpty()) {
                Request* req = nullptr;
                WaitingSR.dequeue(req);
                req->setStatus(COMPLETED);
                req->setFT(tick);
                CompletedTickets.enqueue(req);
                finishedCount++;
                cout << ">> Move 5 (r=" << r << "): SR #" << req->getRID() << " completed.\n";
            } else {
                cout << ">> Move 5 (r=" << r << "): WaitingSR empty.\n";
            }
        }
        else if (r <= 95) {
            //finish pending UR/NR tickets
            if (!WaitingUR.isEmpty()) {
                Request* req = nullptr;
                WaitingUR.dequeue(req);
                req->setStatus(COMPLETED);
                req->setFT(tick);
                CompletedTickets.enqueue(req);
                finishedCount++;
                cout << ">> Move 6 (r=" << r << "): UR #" << req->getRID() << " completed.\n";
            } else if (!WaitingNR.isEmpty()) {
                Request* req = nullptr;
                WaitingNR.dequeue(req);
                req->setStatus(COMPLETED);
                req->setFT(tick);
                CompletedTickets.enqueue(req);
                finishedCount++;
                cout << ">> Move 6 (r=" << r << "): NR #" << req->getRID() << " completed.\n";
            } else {
                cout << ">> Move 6 (r=" << r << "): queues empty.\n";
            }
        }
        else {
            //finish remaining SR ticket
            if (!WaitingSR.isEmpty()) {
                Request* req = nullptr;
                WaitingSR.dequeue(req);
                req->setStatus(COMPLETED);
                req->setFT(tick);
                CompletedTickets.enqueue(req);
                finishedCount++;
                cout << ">> Move 7 (r=" << r << "): SR #" << req->getRID() << " completed.\n";
            } else {
                cout << ">> Move 7 (r=" << r << "): WaitingSR empty.\n";
            }
        }

        printState();
    }

    cout << "               Simulation Finished\n";
    cout << "   Finished (" << finishedCount << ") + Cancelled (" << 
    cancelledCount  << ") == Total (" << totalTickets << ")\n";
}

