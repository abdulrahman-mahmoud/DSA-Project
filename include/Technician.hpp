#ifndef TECHNICIAN
#define TECHNICIAN
#include <string>
#include <iostream>
#include "request.hpp"

using namespace std;


class Technician {
    private:
        int id;
        string type;
        Request* currentRequest;
        int busyTime;

    public:
        Technician();
        Technician(int ids ,const string techType);
        void assign(Request* request);
        void complete();
        void cancelCurrentRequest();
        bool isST() const;
        int getID() const ;
        int getBusyTime() const;

        // added by hassan
        Request* getCurrentRequest() const;
};

#endif