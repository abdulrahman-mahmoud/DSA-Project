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
    while (waitingSR.dequeue(req))        { delete req; }
    while (waitingNR.dequeue(req))        { delete req; }
    while (waitingUR.dequeue(req))        { delete req; }
    while (CompletedTickets.dequeue(req)) { delete req; }
    while (CancelRequests.dequeue(req))   { delete req; }
}

void Organizer::addRequest(Request* req) {
    if (req == nullptr) return;

    if (req->getType() == SR) {
        waitingSR.enqueue(req);
    } else if (req->getType() == UR) {
        waitingUR.enqueue(req);
    } else {
        waitingNR.enqueue(req);
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
    cout << "waitingSR (" << const_cast<WaitingSR&>(waitingSR).getCount() << "): ";
    const_cast<WaitingSR&>(waitingSR).print();

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
            if (!waitingSR.isEmpty()) {
                Request* req = nullptr;
                waitingSR.dequeue(req);
                req->setStatus(COMPLETED);
                req->setFT(tick);
                CompletedTickets.enqueue(req);
                finishedCount++;
                cout << ">> Move 1 (r=" << r << "): SR #" << req->getRID() << " completed.\n";
            } else {
                cout << ">> Move 1 (r=" << r << "): waitingSR empty.\n";
            }
        }
        else if (r <= 45) {
            //NR Ticket finish 
            if (!waitingNR.isEmpty()) {
                Request* req = nullptr;
                waitingNR.dequeue(req);
                req->setStatus(COMPLETED);
                req->setFT(tick);
                CompletedTickets.enqueue(req);
                finishedCount++;
                cout << ">> Move 2 (r=" << r << "): NR #" << req->getRID() << " completed.\n";
            } else {
                cout << ">> Move 2 (r=" << r << "): waitingNR empty.\n";
            }
        }
        else if (r <= 60) {
            //UR Ticket finish
            if (!waitingUR.isEmpty()) {
                Request* req = nullptr;
                waitingUR.dequeue(req);
                req->setStatus(COMPLETED);
                req->setFT(tick);
                CompletedTickets.enqueue(req);
                finishedCount++;
                cout << ">> Move 3 (r=" << r << "): UR #" << req->getRID() << " completed.\n";
            } else {
                cout << ">> Move 3 (r=" << r << "): waitingUR empty.\n";
            }
        }
        else if (r <= 75) {
            //NR Ticket cancelled
            if (!waitingNR.isEmpty()) {
                Request* req = nullptr;
                waitingNR.dequeue(req);
                req->setStatus(CANCELLED);
                CancelRequests.enqueue(req);
                cancelledCount++;
                cout << ">> Move 4 (r=" << r << "): NR #" << req->getRID() << " cancelled.\n";
            } else {
                cout << ">> Move 4 (r=" << r << "): waitingNR empty (no cancel).\n";
            }
        }
        else if (r <= 85) {
            // SR ticket finishes
            if (!waitingSR.isEmpty()) {
                Request* req = nullptr;
                waitingSR.dequeue(req);
                req->setStatus(COMPLETED);
                req->setFT(tick);
                CompletedTickets.enqueue(req);
                finishedCount++;
                cout << ">> Move 5 (r=" << r << "): SR #" << req->getRID() << " completed.\n";
            } else {
                cout << ">> Move 5 (r=" << r << "): waitingSR empty.\n";
            }
        }
        else if (r <= 95) {
            //finish pending UR/NR tickets
            if (!waitingUR.isEmpty()) {
                Request* req = nullptr;
                waitingUR.dequeue(req);
                req->setStatus(COMPLETED);
                req->setFT(tick);
                CompletedTickets.enqueue(req);
                finishedCount++;
                cout << ">> Move 6 (r=" << r << "): UR #" << req->getRID() << " completed.\n";
            } else if (!waitingNR.isEmpty()) {
                Request* req = nullptr;
                waitingNR.dequeue(req);
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
            if (!waitingSR.isEmpty()) {
                Request* req = nullptr;
                waitingSR.dequeue(req);
                req->setStatus(COMPLETED);
                req->setFT(tick);
                CompletedTickets.enqueue(req);
                finishedCount++;
                cout << ">> Move 7 (r=" << r << "): SR #" << req->getRID() << " completed.\n";
            } else {
                cout << ">> Move 7 (r=" << r << "): waitingSR empty.\n";
            }
        }

        printState();
    }

    cout << "               Simulation Finished\n";
    cout << "   Finished (" << finishedCount << ") + Cancelled (" << 
    cancelledCount  << ") == Total (" << totalTickets << ")\n";
}

