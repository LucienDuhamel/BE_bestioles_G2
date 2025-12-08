#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include <string>
#include "EspeceBestiole.h" // Indispensable pour connaître le type EspeceBestiole

struct Snapshot {
    int identite;
    int x;
    int y;
    double orientation;
    double vitesse;
    std::string comportement;

    Snapshot(EspeceBestiole* b);
};

#endif