#ifndef _BestioleFactory_
#define _BestioleFactory_


#include "EspeceBestiole.h"
#include "Comportement.h"
#include "EspeceBestioleFactory.h"
#include <vector>

class BestioleFactory : public EspeceBestioleFactory
{
private:
    std::vector<Comportement*> ListComportements;
    std::vector<double> proportionsAccumilatives;
public :

    BestioleFactory(std::vector<Comportement*> Comportements, std::vector<double> Proportions);
    Bestiole* creerEspeceBestiole() const override;

};


#endif
