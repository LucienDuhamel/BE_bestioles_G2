#include "Comportement.h"
#include "Bestiole.h"
#include "ComportementPersoMultiples.h"
#include "utils.h"
#include <iostream>
#include <vector>
#include <errno.h>

double ComportementPersoMultiples::MAX_PROBA_CHANGEMENT_COMPORTEMENT = 0.0;
bool ComportementPersoMultiples::configInitialized = false;

ComportementPersoMultiples::ComportementPersoMultiples(std::vector<Comportement*> listeComportements)
{
    // On copie la liste des comportements possibles
    for (auto& c : listeComportements)
        comportementsDisponibles.push_back(std::move(c));

    // On choisit une première personnalité au hasard
    ComportementApparentIndex = rand() % comportementsDisponibles.size() ;
    
    // Initialisation de la config si nécessaire
    if(!configInitialized)
    {
        initFromConfig();
        configInitialized = true;
    }
    
    // Chaque bestiole a sa propre instabilité mentale (probabilité de changer)
    probaChangementComportement = static_cast<double>( randomBetween(0.0, MAX_PROBA_CHANGEMENT_COMPORTEMENT) );
}

ComportementPersoMultiples::~ComportementPersoMultiples()
{
    comportementsDisponibles.clear();
}

Comportement* ComportementPersoMultiples::clone() const 
{
    // On doit cloner pour que la nouvelle bestiole ait son propre état
    return new ComportementPersoMultiples(comportementsDisponibles);
}

T * ComportementPersoMultiples::getCouleur()  const {
    // La couleur est celle de la personnalité active
    return comportementsDisponibles[ComportementApparentIndex]->getCouleur();
} 

void ComportementPersoMultiples::reagit(Bestiole& bestiole, const std::vector<EspeceBestiole*>&  listeBestioles )
{   
    if (comportementsDisponibles.empty()) {
        std::cerr << "Erreur : pas de comportements disponibles !\n";
        return;
    }
    
    // Test probabiliste pour changer de personnalité
    if (randomBetween(0.0, 1.0) < probaChangementComportement) {
        
        // Changement d'index (on évite de retomber sur le même avec le modulo size-1)
        int saut = rand() % (comportementsDisponibles.size()-1);
        if (saut == 0) saut = 1; // Sécurité pour s'assurer qu'on change vraiment
        
        ComportementApparentIndex = (ComportementApparentIndex + saut) % comportementsDisponibles.size();
        
        // Si la bestiole change de comportement, on réinitialise sa vitesse 
        // (utile si elle passe de "Peureux" qui court vite à "Grégaire" qui est calme)
        bestiole.setVitesse(bestiole.getVitesseIni());
        
        // On met à jour la couleur pour refléter le changement
        bestiole.setCouleur(comportementsDisponibles[ComportementApparentIndex]->getCouleur());
    }

    // On délègue l'action au comportement actif
    comportementsDisponibles[ComportementApparentIndex]->reagit(bestiole, listeBestioles);
}

// Initialisation des paramètres statiques depuis le fichier de config
void ComportementPersoMultiples::initFromConfig() {
    MAX_PROBA_CHANGEMENT_COMPORTEMENT = Config::getInstance().getDouble("MAX_PROBA_CHANGEMENT_COMPORTEMENT", 0.05);
}