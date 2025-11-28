#include "Comportement.h"
#include "Bestiole.h"
#include "ComportementPersoMultiples.h"
#include "utils.h"
#include <iostream>
#include <vector>
#include <errno.h>



ComportementPersoMultiples::ComportementPersoMultiples(const std::vector<Comportement*>& comportementsDisponibles)
{   

    for (auto& c : comportementsDisponibles)
        listeComportements.push_back(c);
        
    comportementCourant = listeComportements[rand() % listeComportements.size()];
    couleur = new T[ 3 ];
    // Couleur violette (par défaut lors de la première création)
    couleur[ 0 ] = 163;
    couleur[ 1 ] = 73;
    couleur[ 2 ] = 164;
}

ComportementPersoMultiples::~ComportementPersoMultiples()
{
    listeComportements.clear();
}

T * ComportementPersoMultiples::getCouleur()  const {
    return couleur;
} 


void ComportementPersoMultiples::reagit(Bestiole& bestiole, const std::vector<EspeceBestiole*>&  listeBestioles ) 
{   

    if (listeComportements.empty()) {
        std::cerr << "Erreur : pas de comportements disponibles !\n";
        return;
    }
    
    if (randomBetween(0.0, 1.0) < PROBA_CHANGEMENT_COMPORTEMENT)
        comportementCourant = listeComportements[rand() % listeComportements.size()];
    comportementCourant->reagit(bestiole, listeBestioles);
    bestiole.setCouleur(comportementCourant->getCouleur());

}