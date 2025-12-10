#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include <string>
#include "EspeceBestiole.h" 

struct Snapshot {
    /**
     * Constructeur : capture l'état d'une bestiole donnée
     */
    int age;
    int identite;
    int x;
    int y;
    double orientation;
    double vitesse;
    std::string comportement;
    std::vector<std::string> accessoires;

    Snapshot(EspeceBestiole* b);
};

#endif