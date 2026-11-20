#include <iostream>
#include "../include/organizer.hpp"

using namespace std;

int main() {
    cout << "=========================================\n";
    cout << "     DSA Project - Phase 1 Simulation    \n";
    cout << "=========================================\n\n";

    Organizer organizer;
    organizer.loadSampleData();
    organizer.simulate();

    cout << "\nPress Enter to exit";
    cin.get();

    return 0;
}
