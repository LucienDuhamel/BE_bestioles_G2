#include "Simulation.h"
#include "Bestiole.h"      
#include "Comportement.h" 
#include "Etat_Population.h" 
#include <stdexcept>
#include <iostream>
#include <map>

Simulation::Simulation(Milieu& m) 
    : milieu(m), currentTime(0) {}

void Simulation::step() {
    // 1. Faire évoluer le Milieu
    // milieu.step(); 

    // 2. Gestion des décès
    std::vector<Snapshot> mortsRecents = milieu.getAndClearRegistreDeces();
    
    for (const auto& snap : mortsRecents) {
        historiqueDeces.push_back({ currentTime, snap });
    }

    // 3. D'abord, on capture l'état complet
    EtatPopulation etat(currentTime, milieu);
    historique.push_back(etat); 

    int nbG = 0, nbP = 0, nbK = 0, nbPM = 0, nbPr = 0;

    // On itère sur les snapshots
    for (const auto& snap : etat.snapshots) {
        // L'info est déjà stockée sous forme de string dans le Snapshot
        const std::string& nom = snap.comportement; 

        if (nom == "Comportement Gregaire") nbG++;
        else if (nom == "Comportement Peureux") nbP++;
        else if (nom == "Comportement Kamikaze") nbK++;
        else if (nom == "Comportement Perso Multiples") nbPM++;
        else if (nom == "Comportement Prevoyant") nbPr++;
    }

    // Sauvegarde des stats du tour
    statistics.push_back({ currentTime, nbG, nbP, nbK, nbPM, nbPr });

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
        std::map<std::string, std::pair<long, int>> statsAcc; 

        // On cherche dans l'historique les morts survenus dans [t, t_fin[
        for (const auto& archive : historiqueDeces) {
            if (archive.temps >= t && archive.temps < t_fin) {
                
                // On récupère les infos depuis le Snapshot stocké dans 'data'
                int age = archive.data.age; 
                const std::vector<std::string>& listeAccessoires = archive.data.accessoires;

                sommeAge += age;
                nbMorts++;

                if (listeAccessoires.empty()) {
                    statsAcc["Aucun"].first += age;
                    statsAcc["Aucun"].second++;
                }
                
                for (const auto& acc : listeAccessoires) {
                    statsAcc[acc].first += age;
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