#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include "Bestiole.h"

class Snapshot {
public:
    int identite;        // identifiant unique de la bestiole
    double x, y;         // position
    double orientation;  // direction
    double vitesse;      // vitesse
    double taille;       // taille pour affichage
    std::string comportement;

    // Constructeur : crée un snapshot à partir d'une Bestiole
    Snapshot(EspeceBestiole* b);

    ~Snapshot() = default;
};

#endif // SNAPSHOT_H
