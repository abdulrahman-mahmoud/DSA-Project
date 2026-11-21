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
    itUnit = new ITUnit(1, 2);
    locations = nullptr;
    serviceDuration = nullptr;
    problemCount = 0;
}

Organizer::~Organizer() {
    Request* req = nullptr;
    while (waitingSR.dequeue(req))        { delete req; }
    while (waitingNR.dequeue(req))        { delete req; }
    while (waitingUR.dequeue(req))        { delete req; }
    while (CompletedTickets.dequeue(req)) { delete req; }
    while (CancelRequests.dequeue(req))   { delete req; }
    delete itUnit;
    delete locations;
    delete[] serviceDuration;
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

bool Organizer::loadInputFile(const string& filename) {
    ifstream in(filename.c_str());
    if (!in) return false;

    int L;
    in >> L;
    locations = new Locations(L);
    for (int i = 1; i <= L; i++) {
        string name;
        in >> name;
        locations->setLocation(i, name);
    }

    in >> problemCount;
    serviceDuration = new int[problemCount + 1];
    for (int i = 1; i <= problemCount; i++) {
        char cat;
        int dur;
        in >> cat >> dur;
        serviceDuration[i] = dur;
    }

    int stCount, gtCount;
    in >> stCount >> gtCount;
    delete itUnit;
    itUnit = new ITUnit(stCount, gtCount);

    int R;
    in >> R;
    for (int i = 0; i < R; i++) {
        string type;
        in >> type;
        if (type == "NR" || type == "SR") {
            int qt, rid, lid, pc;
            in >> qt >> rid >> lid >> pc;
            RequestType t = (type == "SR") ? SR : NR;
            addRequest(new Request(rid, qt, lid, pc, t, 0));
        } else if (type == "UR") {
            int qt, rid, lid, pc, pr;
            in >> qt >> rid >> lid >> pc >> pr;
            addRequest(new Request(rid, qt, lid, pc, UR, pr));
        }
    }

    int C;
    in >> C;
    for (int i = 0; i < C; i++) {
        int ct, rid;
        in >> ct >> rid;
        // Store cancellation records (do not discard input data).
        cancelRecordCT.enqueue(ct);
        cancelRecordRID.enqueue(rid);
    }

    return true;
}

void Organizer::printState() const {
    cout << "           [Step " << tick << "]\n";
    cout << "WaitingSR (" << const_cast<WaitingSR&>(waitingSR).getCount() << "): ";
    const_cast<WaitingSR&>(waitingSR).print();

    cout << "WaitingNR (" << const_cast<WaitingNR&>(waitingNR).getCount() << "): ";
    const_cast<WaitingNR&>(waitingNR).print();

    cout << "WaitingUR (" << const_cast<WaitingUR&>(waitingUR).getCount() << "): ";
    const_cast<WaitingUR&>(waitingUR).print();

    cout << "Completed (" << const_cast<Queue<Request*>&>(CompletedTickets).getCount() << "): ";
    const_cast<Queue<Request*>&>(CompletedTickets).print();

    cout << "Cancelled (" << const_cast<Queue<Request*>&>(CancelRequests).getCount() << "): ";
    const_cast<Queue<Request*>&>(CancelRequests).print();

    cout << "Progress: Finished=" << finishedCount
         << " + Cancelled=" << cancelledCount
         << " = " << (finishedCount + cancelledCount)
         << " / " << totalTickets << "\n\n";
}

void Organizer::simulate(bool interactive) {
    cout << "       Starting Simulation (Total: " << totalTickets << " Tickets) \n\n";
    printState();

    while (finishedCount + cancelledCount < totalTickets) {
        tick++;

        int r = (rand() % 100) + 1;

        if (r >= 10 && r < 20) {
            if (!waitingUR.isEmpty()) {
                Request* req = nullptr;
                waitingUR.dequeue(req);
                req->setStatus(COMPLETED);
                req->setFT(tick);
                CompletedTickets.enqueue(req);
                finishedCount++;
                cout << ">> UR #" << req->getRID() << " moved to Finished.\n";
            }
        }
        else if (r >= 20 && r < 30) {
            if (!waitingSR.isEmpty()) {
                Request* req = nullptr;
                waitingSR.dequeue(req);
                req->setStatus(COMPLETED);
                req->setFT(tick);
                CompletedTickets.enqueue(req);
                finishedCount++;
                cout << ">> SR #" << req->getRID() << " moved to Finished.\n";
            }
        }
        else if (r >= 30 && r < 45) {
            if (!waitingNR.isEmpty()) {
                Request* req = nullptr;
                waitingNR.dequeue(req);
                req->setStatus(COMPLETED);
                req->setFT(tick);
                CompletedTickets.enqueue(req);
                finishedCount++;
                cout << ">> NR #" << req->getRID() << " moved to Finished.\n";
            }
        }
        else if (r >= 45 && r < 50) {
            if (!waitingNR.isEmpty()) {
                Request* req = nullptr;
                waitingNR.dequeue(req);
                if (req != nullptr) {
                    req->setStatus(CANCELLED);
                    CancelRequests.enqueue(req);
                    cancelledCount++;
                    cout << ">> NR #" << req->getRID() << " cancelled.\n";
                }
            }
        }
        else if (r >= 50 && r < 60) {
            Technician* t = itUnit->getFreeST();
            if (t != nullptr) {
                workingTechs.enqueue(t);
                cout << ">> ST #" << t->getID() << " moved to busy.\n";
            }
        }
        else if (r >= 60 && r < 70) {
            Technician* t = itUnit->getFreeGT();
            if (t != nullptr) {
                workingTechs.enqueue(t);
                cout << ">> GT #" << t->getID() << " moved to busy.\n";
            }
        }
        else if (r >= 70 && r < 85) {
            if (!workingTechs.isEmpty()) {
                Technician* t = nullptr;
                workingTechs.dequeue(t);
                if (t != nullptr) {
                    if (t->isST()) itUnit->returnST(t);
                    else itUnit->returnGT(t);
                    cout << ">> Technician #" << t->getID() << " returned to free.\n";
                }
            }
        }

        printState();
        if (interactive) {
            cout << "Press Enter to advance to the next minute.\n";
            cin.get();
        }
    }

    cout << "               Simulation Finished\n";
    cout << "   Finished (" << finishedCount << ") + Cancelled (" << cancelledCount << ") == Total (" << totalTickets << ")\n";
}