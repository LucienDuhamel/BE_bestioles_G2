#include "Comportement.h"
#include "Bestiole.h"
#include "ComportementPersoMultiples.h"
#include "utils.h"
#include <iostream>
#include <vector>
#include <errno.h>




double      ComportementPersoMultiples::MAX_PROBA_CHANGEMENT_COMPORTEMENT = 0.0;

ComportementPersoMultiples::ComportementPersoMultiples(std::vector<Comportement*> listeComportements)
{
    for (auto& c : listeComportements)
        comportementsDisponibles.push_back(std::move(c));

    ComportementApparentIndex = rand() % comportementsDisponibles.size() ;
    // Initialisation des parametres statiques depuis le fichier de config
   if( MAX_PROBA_CHANGEMENT_COMPORTEMENT == 0.0 )
   {
      initFromConfig();
   }
   probaChangementComportement = static_cast<double>( randomBetween(0.0, MAX_PROBA_CHANGEMENT_COMPORTEMENT) );

}


ComportementPersoMultiples::~ComportementPersoMultiples()
{
    comportementsDisponibles.clear();
}

Comportement*   ComportementPersoMultiples::clone() const 
{
    return new ComportementPersoMultiples(comportementsDisponibles);
}

T * ComportementPersoMultiples::getCouleur()  const {
    return comportementsDisponibles[ComportementApparentIndex]->getCouleur();
} 


void ComportementPersoMultiples::reagit(Bestiole& bestiole, const std::vector<EspeceBestiole*>&  listeBestioles )
{   

    if (comportementsDisponibles.empty()) {
        std::cerr << "Erreur : pas de comportements disponibles !\n";
        return;
    }
    
    if (randomBetween(0.0, 1.0)< probaChangementComportement) {
        
        int saut =  rand() % (comportementsDisponibles.size()-1);
        ComportementApparentIndex = (ComportementApparentIndex + saut) % comportementsDisponibles.size() ;
        
        bestiole.setCouleur(comportementsDisponibles[ComportementApparentIndex]->getCouleur());
    }

    comportementsDisponibles[ComportementApparentIndex]->reagit(bestiole, listeBestioles);

}

// Initialisation des parametres statiques depuis le fichier de config (valeurs par defaut si absentes)
void ComportementPersoMultiples::initFromConfig() {
    MAX_PROBA_CHANGEMENT_COMPORTEMENT = Config::getInstance().getDouble("MAX_PROBA_CHANGEMENT_COMPORTEMENT", 0.05);

}
