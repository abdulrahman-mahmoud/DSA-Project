#ifndef UI_H
#define UI_H

#include <iostream>
#include <string>
#include "WaitingUR.hpp"
#include "WaitingNR.hpp"
#include "queue.hpp"
#include "FreeTechnicianList.hpp"
using namespace std;

class UI {
private:
    bool interactive;        
    string inputFile;
    string outputFile;

public:
    UI();

    void readMode();         
    void readFileNames();    

    bool isInteractive() const;
    string getInputFile() const;
    string getOutputFile() const;

    
    void printScreen(int minute,
                     WaitingUR* ur,
                     Queue<Request*>* sr,
                     WaitingNR* nr,
                     FreeTechnicianList* freeST,
                     FreeTechnicianList* freeGT,
                     Queue<Request*>* completed);

    void waitForEnter();     
    void printSilentStart();
    void printSilentEnd();
};

#endif
