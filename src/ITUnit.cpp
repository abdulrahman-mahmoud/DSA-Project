#include "ITUnit.hpp"

ITUnit::ITUnit(int numberOfST, int numberOfGT) {

    stCount = numberOfST;
    gtCount = numberOfGT;

    technicians = new Technician[stCount + gtCount];

    for (int i = 0; i < stCount; i++) {
        technicians[i] = Technician(i + 1, "ST");
        freeST.insert(&technicians[i]);
    }

    for (int i = 0; i < gtCount; i++) {
        technicians[stCount + i] =
            Technician(stCount + i + 1, "GT");

        freeGT.insert(&technicians[stCount + i]);
    }
}

ITUnit::~ITUnit() {
    delete[] technicians;
}
