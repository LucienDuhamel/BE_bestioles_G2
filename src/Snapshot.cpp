#include "Snapshot.h"

// Constructeur : copie les valeurs de la Bestiole
Snapshot::Snapshot(EspeceBestiole* b) {
    identite    = b->getidentite();
    x           = b->getx();
    y           = b->gety();
    orientation = b->getorientation();
    vitesse     = b->getVitesse();
    comportement = b->getComportement()->getName();
}
