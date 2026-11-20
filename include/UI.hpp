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
    bool interactive;        // true = Interactive, false = Silent
    string inputFile;
    string outputFile;

public:
    UI();

    void readMode();         // asks the user for the mode
    void readFileNames();    // asks for input and output file names

    bool isInteractive() const;
    string getInputFile() const;
    string getOutputFile() const;

    // prints one minute of the simulation by calling print() on each list
    void printScreen(int minute,
                     WaitingUR* ur,
                     Queue<Request*>* sr,
                     WaitingNR* nr,
                     FreeTechnicianList* freeST,
                     FreeTechnicianList* freeGT,
                     Queue<Request*>* completed);

    void waitForEnter();     // Interactive mode: pause until Enter
    void printSilentStart();
    void printSilentEnd();
};

#endif