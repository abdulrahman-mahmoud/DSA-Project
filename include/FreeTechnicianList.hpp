#ifndef FREE_TECHNICIAN_LIST
#define FREE_TECHNICIAN_LIST

#include "PriQueue.hpp"
#include "Technician.hpp"

class FreeTechnicianList : public PriQueue<Technician*> {
public:
    bool isHigher(Technician* const& a, Technician* const& b) const override;

    void insert(Technician* technician);
    Technician* remove();
    void print() const;
};

#endif
