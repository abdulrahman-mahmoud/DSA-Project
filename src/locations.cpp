#include "../include/locations.hpp"

// array ds

Locations::Locations(int numberOfLocations) {
    count = numberOfLocations;

    // leave index 0 not used so we can start at index 1 
    locationNames = new string[count + 1];
}

Locations::~Locations() {
    delete[] locationNames;
}

void Locations::setLocation(int id, const string& name) {
    if (id < 1 || id > count) {
        return;
    }

    locationNames[id] = name;
}

string Locations::getLocation(int id) const {
    if (id < 1 || id > count) {
        return "";
    }

    return locationNames[id];
}

int Locations::getCount() const {
    return count;
}
