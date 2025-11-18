#include "Bestiole.h"
#include "ComportementPeureux.h"
#include <iostream>
#include <vector>



ComportementPeureux*   ComportementPeureux::getInstance()
{
    if (singletonPeureux == nullptr)
        singletonPeureux = new ComportementPeureux();

    return  singletonPeureux;
}


void ComportementPeureux::bouge(Bestiole bestiole, std::vector<EspeceBestiole*>   listeBestioles ) const 
{
    
}