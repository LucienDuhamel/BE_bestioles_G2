#include "Simulation.h"
#include <stdexcept>
#include <iostream>

Simulation::Simulation(Milieu& m) 
    : milieu(m), currentTime(0) {}

// Avancer d'un pas : mouvement + capture de l'état
void Simulation::step() {
    // 1. Faire évoluer le Milieu
    milieu.step();

    int nbG = 0;
    int nbP = 0;
    int nbK = 0;
    int nbPM = 0;
    int nbPr = 0;

    const auto& bestioles = milieu.getListeEspeceBestioles();
    for (const auto* e : bestioles) {
        const Bestiole* b = dynamic_cast<const Bestiole*>(e);
        if (!b) continue;

        if (b->getComportement()->getName() == "Comportement Gregaire")
            nbG++;
        else if (b->getComportement()->getName() == "Comportement Peureuse")
            nbP++;
        else if (b->getComportement()->getName() == "Comportement Kamikaze")
            nbK++;
        else if (b->getComportement()->getName() == "Comportement Perso Multiples")
            nbPM++;
        else if (b->getComportement()->getName() == "Comportement Prevoyant")
            nbPr++; 
    }

    statistics.push_back({ currentTime, nbG, nbP, nbK, nbPM, nbPr });

    // 2. Capturer l'état courant
    EtatPopulation etat(currentTime, milieu);
    historique.push_back(etat);

    // 3. Incrémenter le temps
    currentTime++;
}

// Exécuter plusieurs pas de simulation
void Simulation::run(int nbPas) {
    for (int i = 0; i < nbPas; ++i) {
        step();
    }
}

// Accès à l'état d'un pas précis
const EtatPopulation& Simulation::getEtat(int pas) const {
    if (pas < 0 || pas >= (int)historique.size()) {
        throw std::out_of_range("Pas de simulation invalide");
    }
    return historique[pas];
}

// Accès au dernier état (bilan final)
const EtatPopulation& Simulation::getDernierEtat() const {
    if (historique.empty()) {
        throw std::runtime_error("Aucun état disponible");
    }
    return historique.back();
}
