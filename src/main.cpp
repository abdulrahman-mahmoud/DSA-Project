#include <iostream>
#include <cassert>

#include "../include/stack.hpp"
#include "../include/locations.hpp"
#include "../include/WorkingTechs.hpp"

using namespace std;

int main() {

    cout << "===== PHASE 1.2 DATA STRUCTURE TESTS =====\n\n";

    // STACK TEST

    cout << "Testing Stack...\n";

    Stack<int> s;

    assert(s.isEmpty());

    s.push(10);
    s.push(20);
    s.push(30);

    assert(s.size() == 3);
    assert(s.peek() == 30);
    assert(s.pop() == 30);
    assert(s.pop() == 20);
    assert(s.pop() == 10);
    assert(s.isEmpty());

    cout << "Stack: PASSED\n\n";

    // LOCATIONS TEST

    cout << "Testing Locations...\n";

    Locations locations(3);

    locations.setLocation(1, "CSAI");
    locations.setLocation(2, "LAB1");
    locations.setLocation(3, "ADMIN");

    assert(locations.getCount() == 3);
    assert(locations.getLocation(1) == "CSAI");
    assert(locations.getLocation(2) == "LAB1");
    assert(locations.getLocation(3) == "ADMIN");
    assert(locations.getLocation(4) == "");

    cout << "Locations: PASSED\n\n";

    // WORKING TECHNICIANS TEST

    cout << "Testing WorkingTechs...\n";

    // create 3 sample request
    Request r1(20, 1, 1, 1, NR, 0);
    Request r2(30, 1, 1, 1, NR, 0);
    Request r3(10, 1, 1, 1, NR, 0);

    // set request finish time
    r1.setFT(8);
    r2.setFT(5);
    r3.setFT(5);

    // create 3 sample technician object
    Technician t1(1, "GT");
    Technician t2(2, "GT");
    Technician t3(3, "GT");

    // give each technician one sample request
    t1.assign(&r1);
    t2.assign(&r2);
    t3.assign(&r3);

    // priority queue object
    WorkingTechs working;

    working.enqueue(&t1);
    working.enqueue(&t2);
    working.enqueue(&t3);

    Technician* finished;

    working.dequeue(finished);
    assert(finished->getID() == 3);

    working.dequeue(finished);
    assert(finished->getID() == 2);

    working.dequeue(finished);
    assert(finished->getID() == 1);

    assert(working.isEmpty());

    cout << "WorkingTechs: PASSED\n\n";


    cout << "===== ALL TESTS PASSED =====\n";

    return 0;
}
