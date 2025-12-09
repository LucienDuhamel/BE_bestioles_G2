#include "Simulation.h"
#include "Bestiole.h"      
#include "Comportement.h"  
#include <stdexcept>
#include <iostream>
#include <map>

Simulation::Simulation(Milieu& m) 
    : milieu(m), currentTime(0) {}

void Simulation::step() {
    // 1. Faire évoluer le Milieu
    milieu.step();

    // Compteurs pour les comportements
    int nbG = 0, nbP = 0, nbK = 0, nbPM = 0, nbPr = 0;

    // 2. Gestion des décès
    // On récupère les morts du tour (Milieu doit nous les donner et vider sa liste interne)
    std::vector<StatMortalite> mortsRecents = milieu.getAndClearRegistreDeces();

    // Archivage pour le bilan final
    for (const auto& mort : mortsRecents) {
        ArchiveDeces archive;
        archive.temps = currentTime;
        archive.ageAuDeces = mort.ageAuDeces;
        archive.accessoires = mort.accessoires; 
        
        historiqueDeces.push_back(archive);
    }

    // 3. Recensement de la population vivante
    const auto& bestioles = milieu.getListeEspeceBestioles();
    for (const auto* e : bestioles) {
        const Bestiole* b = dynamic_cast<const Bestiole*>(e);
        if (!b) continue;

        if (b->getComportement()) {
            std::string nom = b->getComportement()->getName();

            if (nom == "Comportement Gregaire") nbG++;
            else if (nom == "Comportement Peureux") nbP++;
            else if (nom == "Comportement Kamikaze") nbK++;
            else if (nom == "Comportement Perso Multiples") nbPM++;
            else if (nom == "Comportement Prevoyant") nbPr++;
        }
    }

    // Sauvegarde des stats du tour
    statistics.push_back({ currentTime, nbG, nbP, nbK, nbPM, nbPr });

    // 4. Capture de l'état visuel/global
    EtatPopulation etat(currentTime, milieu);
    historique.push_back(etat);

    // 5. Incrémenter le temps
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

void Simulation::afficherBilanFinal() const {
    std::cout << "\n=== BILAN FINAL DE LA SIMULATION (Par tranches de 100 pas) ===" << std::endl;

    if (historiqueDeces.empty()) {
        std::cout << "Aucun deces enregistre." << std::endl;
        return;
    }

    int finSimulation = currentTime;
    int pasDeTemps = 100; 

    // On parcourt le temps par bonds de 100
    for (int t = 0; t < finSimulation; t += pasDeTemps) {
        int t_fin = t + pasDeTemps;
        
        // Variables pour les stats de cette tranche
        long sommeAge = 0;
        int nbMorts = 0;
        std::map<std::string, std::pair<long, int>> statsAcc; // Nom -> {SommeAge, Nombre}

        // On cherche dans l'historique les morts survenus dans [t, t_fin[
        for (const auto& mort : historiqueDeces) {
            if (mort.temps >= t && mort.temps < t_fin) {
                sommeAge += mort.ageAuDeces;
                nbMorts++;

                if (mort.accessoires.empty()) {
                    statsAcc["Aucun"].first += mort.ageAuDeces;
                    statsAcc["Aucun"].second++;
                }
                for (const auto& acc : mort.accessoires) {
                    statsAcc[acc].first += mort.ageAuDeces;
                    statsAcc[acc].second++;
                }
            }
        }

        // Affichage pour cette tranche si des données existent
        if (nbMorts > 0) {
            std::cout << "\n[Periode " << t << " - " << t_fin << "]" << std::endl;
            std::cout << "  - Mortalite globale : " << nbMorts << " morts, Age moyen : " 
                      << (double)sommeAge / nbMorts << " pas" << std::endl;
            
            for (auto const& [nom, data] : statsAcc) {
                if (data.second > 0) {
                    double moy = (double)data.first / data.second;
                    std::cout << "    * " << nom << " : " << moy << " (sur " << data.second << " ind.)" << std::endl;
                }
            }
        }
    }
    std::cout << "\n==============================================================" << std::endl;
}