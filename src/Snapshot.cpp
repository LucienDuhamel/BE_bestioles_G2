#include "Snapshot.h"
#include "Comportement.h" 

// Constructeur : copie les valeurs de la Bestiole
Snapshot::Snapshot(EspeceBestiole* b) {
    identite    = b->getId();
    x           = b->getX();
    y           = b->getY();
    orientation = b->getOrientation();
    vitesse     = b->getVitesse();
    
    if (b->getComportement() != nullptr) {
        comportement = b->getComportement()->getName();
    } else {
        comportement = "Inconnu";
    }
}