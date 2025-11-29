#include "Comportement.h"
#include "Bestiole.h"
#include "ComportementPersoMultiples.h"
#include "utils.h"
#include <iostream>
#include <vector>
#include <errno.h>



ComportementPersoMultiples* ComportementPersoMultiples::singletonPersoMultiples = nullptr;



ComportementPersoMultiples::ComportementPersoMultiples(std::vector<Comportement*> listeComportements)
{
    for (auto& c : listeComportements)
        comportementsDisponibles.push_back(std::move(c));
}

ComportementPersoMultiples::~ComportementPersoMultiples()
{
    comportementsDisponibles.clear();
}

ComportementPersoMultiples*   ComportementPersoMultiples::getInstance(std::vector<Comportement*> listeComportements)
{
    if (singletonPersoMultiples == nullptr){
        singletonPersoMultiples = new ComportementPersoMultiples(listeComportements);
        singletonPersoMultiples->couleur = new T[ 3 ];
        // Couleur noire
        singletonPersoMultiples->couleur[ 0 ] = 0;
        singletonPersoMultiples->couleur[ 1 ] = 0;
        singletonPersoMultiples->couleur[ 2 ] = 0;

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

    if (comportementsDisponibles.empty()) {
        std::cerr << "Erreur : pas de comportements disponibles !\n";
        return;
    }
    
    if (randomBetween(0.0, 1.0)< bestiole.getProbaChangementComportement()) {
        Comportement* nouveauComportement = comportementsDisponibles[rand() % comportementsDisponibles.size()];
        bestiole.setComportementApparent(nouveauComportement);
        nouveauComportement->reagit(bestiole, listeBestioles);
        bestiole.setCouleur(nouveauComportement->getCouleur());
    }

    else {
        bestiole.getComportementApparent()->reagit(bestiole, listeBestioles);
    }

}