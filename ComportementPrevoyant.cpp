#include "Bestiole.h"
#include "ComportementPrevoyant.h"
#include <iostream>
#include <vector>


ComportementPrevoyant* ComportementPrevoyant::singletonPrevoyant = nullptr;

ComportementPrevoyant*   ComportementPrevoyant::getInstance()
{
    if (singletonPrevoyant == nullptr)
        singletonPrevoyant = new ComportementPrevoyant();

    return  singletonPrevoyant;
}


void ComportementPrevoyant::bouge(Bestiole& bestiole, std::vector<EspeceBestiole*>   listeBestioles ) const 
{
    
}