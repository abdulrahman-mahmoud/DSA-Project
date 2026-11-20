#include "ITUnit.hpp"

ITUnit::ITUnit(int numberOfST, int numberOfGT) {

    stCount = numberOfST;
    gtCount = numberOfGT;

    technicians = new Technician[stCount + gtCount];

    for (int i = 0; i < stCount; i++) {
        technicians[i] = Technician(i + 1, "ST");
        freeST.insert(&technicians[i]);
    }

    for (int i = 0; i < gtCount; i++) {
        technicians[stCount + i] =
            Technician(stCount + i + 1, "GT");

        freeGT.insert(&technicians[stCount + i]);
    }
}

Technician* ITUnit::getFreeST(){
    return freeST.remove();
};

Technician* ITUnit::getFreeGT(){
    return freeGT.remove();
};

void ITUnit::returnST(Technician* technician){
    freeST.insert(technician);
}

void ITUnit::returnGT(Technician* technician){
    freeGT.insert(technician);
}

void ITUnit::addWaitingNR(Request* request){
    waitingNR.enqueue(request);
}

Request* ITUnit::getWaitingNR(){
    Request* request = nullptr;
    waitingNR.dequeue(request);
    return request;
}

Request* ITUnit::cancelWaitingNR(int rid){
    return waitingNR.cancelByRID(rid);
}

int ITUnit::getWaitingNRCount() const{
    return waitingNR.getCount();
}

ITUnit::~ITUnit() {
    delete[] technicians;
}