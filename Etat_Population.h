#ifndef ETATPOPULATION_H
#define ETATPOPULATION_H

#include <vector>
#include "Snapshot.h"
#include "Milieu.h"

class EtatPopulation {
private:
    int timestamp;  // temps ou numéro du pas de simulation

public:
    std::vector<Snapshot> snapshots;  // état de toutes les bestioles à ce moment

    // Constructeur : capture l'état actuel d'un Milieu
    EtatPopulation(int t, const Milieu& m);

    // Getter du timestamp
    int getTimestamp() const { return timestamp; }

    // Destructeur
    ~EtatPopulation() = default;
};

#endif // ETATPOPULATION_H
