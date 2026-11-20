/*
it manges the it dep all , from Waiting NR SR UR and Techniacal 
*/

#ifndef ITUNIT
#define ITUNIT

#include "Technician.hpp"
#include "FreeTechnicianList.hpp"
#include "WaitingNR.hpp"

class ITUnit {
private:

    FreeTechnicianList freeST;
    FreeTechnicianList freeGT;

    WaitingNR waitingNR;

    Technician* technicians;

    int stCount;
    int gtCount;

public:

    ITUnit(int numberOfST, int numberOfGT);
    // Technician stuff
    Technician* getFreeST();
    Technician* getFreeGT();
    
    void returnST(Technician* technician);
    void returnGT(Technician* technician);

    // Tickets stuff 
    void addWaitingNR(Request* request);
    Request* getWaitingNR();
    Request* cancelWaitingNR(int rid);
    int getWaitingNRCount() const;

    ~ITUnit();

};

#endif