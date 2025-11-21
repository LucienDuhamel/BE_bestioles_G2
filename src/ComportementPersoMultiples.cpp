#include "Comportement.h"
#include "Bestiole.h"
#include "ComportementPersoMultiples.h"
#include <iostream>
#include <vector>
#include <errno.h>

ComportementPersoMultiples* ComportementPersoMultiples::singletonPersoMultiples = nullptr;



ComportementPersoMultiples::ComportementPersoMultiples(const std::vector<Comportement*>& comportementsDisponibles)
{   

    for (auto& c : comportementsDisponibles)
        listeComportements.push_back(std::move(c));
}

ComportementPersoMultiples::~ComportementPersoMultiples()
{
    listeComportements.clear();
}

ComportementPersoMultiples*   ComportementPersoMultiples::getInstance(const std::vector<Comportement*>& listeComportements)
{
    if (singletonPersoMultiples == nullptr){
        singletonPersoMultiples = new ComportementPersoMultiples(listeComportements);
        singletonPersoMultiples->couleur = new T[ 3 ];

        // Couleur violette (par défaut lors de la première création)
        singletonPersoMultiples->couleur[ 0 ] = 163;
        singletonPersoMultiples->couleur[ 1 ] = 73;
        singletonPersoMultiples->couleur[ 2 ] = 164;

    }

    return  singletonPersoMultiples;
}

ComportementPersoMultiples*   ComportementPersoMultiples::getInstance()
{
    if (singletonPersoMultiples == nullptr)
        std::cerr <<"ComportementPersoMultiples instance not initialized with ListComportement!" << std::endl;

    return  singletonPersoMultiples;
}

T * ComportementPersoMultiples::getCouleur()  const {
    return couleur;
} 


void ComportementPersoMultiples::reagit(Bestiole& bestiole, const std::vector<EspeceBestiole*>&  listeBestioles ) const 
{   

    if (listeComportements.empty()) {
        std::cerr << "Erreur : pas de comportements disponibles !\n";
        return;
    }

    Comportement* comportementCourant;
    comportementCourant = listeComportements[rand() % listeComportements.size()];
    comportementCourant->reagit(bestiole, listeBestioles);
    bestiole.setCouleur(comportementCourant->getCouleur());

}