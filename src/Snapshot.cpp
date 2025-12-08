#include "Snapshot.h"
#include "Comportement.h" // Nécessaire pour appeler getName()

// Constructeur : copie les valeurs de la Bestiole
Snapshot::Snapshot(EspeceBestiole* b) {
    // Utilisation des getters standardisés (Majuscules)
    identite    = b->getId();
    x           = b->getX();
    y           = b->getY();
    orientation = b->getOrientation();
    vitesse     = b->getVitesse();
    
    // Vérification de sécurité : si c'est une EspeceBestiole de base (pas Bestiole),
    // getComportement() peut renvoyer nullptr.
    if (b->getComportement() != nullptr) {
        comportement = b->getComportement()->getName();
    } else {
        comportement = "Inconnu";
    }
}