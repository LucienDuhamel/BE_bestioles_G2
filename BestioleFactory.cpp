


#include "Bestiole.h"
#include "Comportement.h"
#include <vector>
#include "BestioleFactory.h"
#include <cassert>

BestioleFactory::~BestioleFactory()
{
    ListComportements.clear();
    proportionsAccumilatives.clear();
}

BestioleFactory::BestioleFactory(std::vector<Comportement*> Comportements, std::vector<double> Proportions)
{
    assert(!Comportements.empty());
    assert(Comportements.size() == Proportions.size());
    
    double accum=0.0;
    for (double x : Proportions ) accum+=x;
    assert( accum==1.0);

    ListComportements.clear();
    for (auto& c : Comportements)
        ListComportements.push_back(std::move(c));

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
    bestiole->setComportement(ListComportements[i]);
    bestiole->setCouleur(ListComportements[i]->getCouleur());
    
    return bestiole;

}