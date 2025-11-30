#include "Bestiole.h"
#include "Comportement.h"
#include <vector>
#include "BestioleFactory.h"
#include <cassert>

#include "Yeux.h"
#include "Oreilles.h"
#include "Carapace.h"
#include "Nageoires.h"
#include "Camouflage.h"
#include <cstdlib>

BestioleFactory::~BestioleFactory()
{
    listeComportements.clear();
    proportionsAccumilatives.clear();
}

BestioleFactory::BestioleFactory(std::vector<Comportement*> Comportements, std::vector<double> Proportions)
{
    assert(!Comportements.empty());
    assert(Comportements.size() == Proportions.size());
    
    double accum=0.0;
    for (double x : Proportions ) accum+=x;
    assert( accum==1.0);

    listeComportements.clear();
    for (auto& c : Comportements)
        listeComportements.push_back(std::move(c));

    proportionsAccumilatives.clear();
    proportionsAccumilatives.push_back(Proportions[0]);
    for (int i=1; i<(int)Proportions.size();i++ )
        proportionsAccumilatives.push_back(proportionsAccumilatives.back()+Proportions[i]);
}

Bestiole* BestioleFactory::creerEspeceBestiole() const
{
    Bestiole* bestiole = new Bestiole();
    double typeProb = static_cast<double>( rand() )/RAND_MAX;
    int i=0;
    while( i<(int)proportionsAccumilatives.size()-1 && typeProb>=proportionsAccumilatives[i] ) i++ ;
    // if (listeComportements[i]->getNom() == "PersoMultiples") {
    //     Comportement* comportementPersoMultiples = new ComportementPersoMultiples(listeComportements);
    // }
    bestiole->setComportement(listeComportements[i]);
    bestiole->setComportementApparent(listeComportements[i]);
    bestiole->setCouleur(listeComportements[i]->getCouleur());
    
    // Chaque capteur a 50% de chance d'être présent (indépendamment des autres)
    if (rand() % 2 == 0) {
        bestiole->addCapteur(new Yeux());
    }

    if (rand() % 2 == 0) {
        bestiole->addCapteur(new Oreilles());
    }

    // Chaque accessoire a 50% de chance d'être présent

    if (rand() % 4 == 0) {
        bestiole->addAccessoire(new Carapace());
    }

    if (rand() % 2 == 0) {
        bestiole->addAccessoire(new Nageoires());
    }

    if (rand() % 2 == 0) {
        bestiole->addAccessoire(new Camouflage());
    }

    return bestiole;

}