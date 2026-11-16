#ifndef LOCATIONS_H
#define LOCATIONS_H

#include <string>
using namespace std;

class Locations {
private:
    string* locationNames;
    int count;

public:
    Locations(int numberOfLocations);
    ~Locations();

    void setLocation(int id, const string& name);
    string getLocation(int id) const;

    int getCount() const;
};

#endif

/* in main() during runtime there will only be 1 locations object
   that all other functions or operations use*/