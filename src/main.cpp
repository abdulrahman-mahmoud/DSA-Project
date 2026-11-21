#include <iostream>
#include <string>

#include "../include/organizer.hpp"
#include "../include/UI.hpp"

using namespace std;

int main() {
    cout << "IT SUPPORT\n\n";
    cout << "University IT Support Management System\n";

    UI ui;
    ui.readMode();
    ui.readFileNames();

    string inputFile = ui.getInputFile();
    bool interactive = ui.isInteractive();

    Organizer org;
    if (!org.loadInputFile(inputFile)) {
        cout << "Failed to load input file: " << inputFile << "\n";
        cout << "Press Enter to close...";
        cin.get();
        return 1;
    }

    if (!interactive) {
        ui.printSilentStart();
    }

    org.simulate(interactive);

    if (!interactive) {
        ui.printSilentEnd();
    }

    cout << "Simulation ends.\n";
    cout << "Press Enter to close...";
    cin.get();
    return 0;
}