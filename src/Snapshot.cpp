#include "Snapshot.h"
#include "Comportement.h" 
#include "Bestiole.h"
#include "IAccessoire.h"

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

    Bestiole* bestioleConcrete = dynamic_cast<Bestiole*>(b);
    
    if (bestioleConcrete != nullptr) {
        age = bestioleConcrete->getAge();
        // On parcourt la liste des accessoires portés
        for (auto accessoire : bestioleConcrete->getListeAccessoire()) {
            if (accessoire) {
                accessoires.push_back(accessoire->getLabel());
            }
        }
    }
}