#ifndef TECHNICIAN
#define TECHNICIAN
#include <string>
#include <iostream>
#include "include\request.hpp"

using namespace std;


class Technician {
    private:
        int id;
        string type;
        Request* currentRequest;
        int busyTime;

    public:
    Technician(int ids ,const string techType);
    void assign(Request* request);
    void complete();
    void cancelCurrentRequest();
    bool isST() const;
    int getID() const ;
    int getBusyTime() const;
};



#endif