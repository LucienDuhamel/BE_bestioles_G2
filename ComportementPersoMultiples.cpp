#include "Comportement.h"
#include "Bestiole.h"
#include "ComportementPersoMultiples.h"
#include <iostream>
#include <vector>



ComportementPersoMultiples::ComportementPersoMultiples(std::vector<Comportement*> ListComportement) : ListComportements(ListComportement) 
{}

ComportementPersoMultiples&  ComportementPersoMultiples::getInstance(std::vector<Comportement*> ListComportement)
{
    if (singletonPersoMultiples == nullptr)
        singletonPersoMultiples = new ComportementPersoMultiples(ListComportement);

    return *singletonPersoMultiples;
}

void ComportementPersoMultiples::bouge(Bestiole bestiole, std::vector<Bestiole>   listeBestioles ) const 
{
    ListComportements[rand() % 4]->bouge(bestiole, listeBestioles);

}