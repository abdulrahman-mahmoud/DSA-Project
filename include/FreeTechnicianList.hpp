#ifndef FREE_TECHNICIAN_LIST
#define FREE_TECHNICIAN_LIST

#include "node.hpp"
#include "Technician.hpp"

class FreeTechnicianList {
private:
    Node<Technician*>* front;
    int count;

public:
    FreeTechnicianList();

    void insert(Technician* technician);
    void print() const;
    Technician* remove();

    bool isEmpty() const;
    int getCount() const;

    ~FreeTechnicianList();
};

#endif