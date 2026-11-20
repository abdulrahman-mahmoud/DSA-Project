#include "UI.hpp"

UI::UI() {
    interactive = true;
}

void UI::readMode() {
    int choice;
    cout << "Choose mode (1 = Interactive, 2 = Silent): ";
    cin >> choice;

    while (choice != 1 && choice != 2) {
        cout << "Invalid choice. Please enter 1 for Interactive or 2 for Silent: ";
        cin >> choice;
    }

    interactive = (choice == 1);
}

void UI::readFileNames() {
    cout << "Input file name: ";
    cin >> inputFile;
    cout << "Output file name: ";
    cin >> outputFile;
    cin.ignore(1000, '\n');      
}

bool UI::isInteractive() const { return interactive; }
string UI::getInputFile() const { return inputFile; }
string UI::getOutputFile() const { return outputFile; }

void UI::printScreen(int minute, WaitingUR* ur, Queue<Request*>* sr,
                     WaitingNR* nr, FreeTechnicianList* freeST,
                     FreeTechnicianList* freeGT, Queue<Request*>* completed) {

    cout << "Minute: " << minute << endl;

    cout << "Waiting UR (priority, QT, RID): ";
    ur->print();

    cout << "Waiting SR (FCFS): ";
    sr->print();

    cout << "Waiting NR (FCFS): ";
    nr->print();

    cout << "Available ST: ";
    freeST->print();

    cout << "Available GT: ";
    freeGT->print();

    cout << "Completed: ";
    completed->print();
}

void UI::waitForEnter() {
    cout << "Press Enter to continue...";
    cin.get();                   
}

void UI::printSilentStart() {
    cout << "Silent Mode" << endl;
    cout << "Simulation Starts..." << endl;
}

void UI::printSilentEnd() {
    cout << "Simulation ends, Output file created" << endl;
}
