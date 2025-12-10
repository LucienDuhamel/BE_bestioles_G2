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
    comportementApparentIndex = rand() % comportementsDisponibles.size() ;
    
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


/**
 * @brief Comportement personnalisé multi-types : change de comportement aléatoirement.
 * 
 * Cette bestiole adopte aléatoirement un des comportements qui lui sont associés
 * créant ainsi un profil imprévisible.
 * 
 * @param bestiole La bestiole qui adopte ce comportement
 * @param listeBestioles Liste de toutes les bestioles du milieu
 * 
 * @details
 * - Chaque étape, avec probabilité MAX_PROBA_CHANGEMENT_COMPORTEMENT :
 *   - Bascule vers un autre type de comportement (sélection aléatoire)
 *   - Mets à jour la couleur affichée pour refléter le comportement courant
 * - Délègue l'action au comportement actif qui exécute sa logique propre
 * 
 * @note Chaque bestiole PersoMultiples a ses propres clones de comportements,
 *       évitant les collisions d'état entre individus.
 */
void ComportementPersoMultiples::reagit(Bestiole& bestiole, const std::vector<EspeceBestiole*>&  listeBestioles )
{   
    if (comportementsDisponibles.empty()) {
        std::cerr << "Erreur : pas de comportements disponibles !\n";
        return;
    }
    
    // Test probabiliste pour changer de personnalité
    if (randomBetween(0.0, 1.0) < probaChangementComportement) {
        
        int saut = rand() % (comportementsDisponibles.size()-1);
        if (saut == 0) saut = 1;
        
        comportementApparentIndex = (comportementApparentIndex + saut) % comportementsDisponibles.size();
        
        // Si la bestiole change de comportement, on réinitialise sa vitesse 
        // (utile si elle passe de "Peureux" à un autre comportement notamment)
        bestiole.setVitesse(bestiole.getVitesseIni());
        

        bestiole.setCouleur(comportementsDisponibles[comportementApparentIndex]->getCouleur());
    }


    comportementsDisponibles[comportementApparentIndex]->reagit(bestiole, listeBestioles);
}


T * ComportementPersoMultiples::getCouleur()  const {
    return comportementsDisponibles[comportementApparentIndex]->getCouleur();
} 


void ComportementPersoMultiples::initFromConfig() {
    MAX_PROBA_CHANGEMENT_COMPORTEMENT = Config::getInstance().getDouble("MAX_PROBA_CHANGEMENT_COMPORTEMENT", 0.05);
}