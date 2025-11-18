#include "Bestiole.h"
#include "ComportementGregaire.h"
#include <iostream>
#include <vector>

ComportementGregaire* ComportementGregaire::singletonGregaire = nullptr;

ComportementGregaire*  ComportementGregaire::getInstance()
{
    if (singletonGregaire == nullptr)
        singletonGregaire = new ComportementGregaire();

    return  singletonGregaire;
}

void ComportementGregaire::bouge(Bestiole bestiole, std::vector<EspeceBestiole*>   listeBestioles ) const 
{

}