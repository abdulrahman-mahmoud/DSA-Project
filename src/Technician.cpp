#include "include/Technician.hpp"
#include <string>
#include <iostream>
using namespace std;

Technician::Technician(int ids, const string techType) {
    id = ids;
    type =  techType;
    currentRequest = nullptr;
    busyTime = 0;
}

int Technician::getID() const {
    return id;
}
int Technician::getBusyTime()const{
    return busyTime;
}
bool Technician::isST()const{
    if(type == "ST" || type == "st"){
        return true;
    }
    else{
        return false;
    }
}
void Technician:: assign(Request* request){
    currentRequest = request;
}
void Technician:: complete(){
    if(currentRequest != nullptr){
        currentRequest->setStatus(COMPLETED);
        currentRequest = nullptr;
    }
}

void Technician::cancelCurrentRequest() {
    if (currentRequest != nullptr) {
        currentRequest->setStatus(CANCELLED);
        currentRequest = nullptr;
    }
}