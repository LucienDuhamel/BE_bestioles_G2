#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include "Milieu.h"
#include "Etat_Population.h"

struct Stat{
    int time;
    int nbGreguaires;
    int nbPeureuses;
    int nbKamikazes;
    int nbPersoMultiples;
    int nbPrevoyants;
};

class Simulation {
private:
    Milieu& milieu;                           // référence au Milieu
    int currentTime;                          // numéro du pas de simulation
    std::vector<EtatPopulation> historique;  // tous les états capturés
    std::vector<Stat> statistics;          // statistiques de la simulation

public: 
    // Constructeur : associe la simulation à un Milieu
    Simulation(Milieu& m);

    // Avancer d'un pas : bouge les bestioles et capture l'état
    void step();

    // Exécuter plusieurs pas de simulation
    void run(int nbPas);

    // Accès à l'état d'un pas précis
    const EtatPopulation& getEtat(int pas) const;

    // Accès au dernier état (bilan final)
    const EtatPopulation& getDernierEtat() const;

    // Accès à l'historique complet
    const std::vector<EtatPopulation>& getHistorique() const { return historique; }

    // Accès aux statistiques
    const std::vector<Stat>& getStatistics() const { return statistics; }
};

#endif // SIMULATION_H
