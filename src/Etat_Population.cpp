#include "Etat_Population.h"

EtatPopulation::EtatPopulation(int t, const Milieu& m) : timestamp(t) {
    // On récupère la liste des bestioles dans le Milieu
    const auto& bestioles = m.getListeEspeceBestioles();

    // Pour chaque bestiole, on crée un Snapshot et on l'ajoute au vecteur
    for (auto* b : bestioles) {
        if (b) {
            snapshots.emplace_back(b);
        }
    }
}
