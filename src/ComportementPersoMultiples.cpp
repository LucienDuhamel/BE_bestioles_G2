#include "Comportement.h"
#include "Bestiole.h"
#include "ComportementPersoMultiples.h"
#include <iostream>
#include <vector>
#include <errno.h>

ComportementPersoMultiples* ComportementPersoMultiples::singletonPersoMultiples = nullptr;



ComportementPersoMultiples::ComportementPersoMultiples(std::vector<Comportement*> ListComportement)
{
    for (auto& c : ListComportement)
        ListComportements.push_back(std::move(c));
}

ComportementPersoMultiples::~ComportementPersoMultiples()
{
    ListComportements.clear();
}

ComportementPersoMultiples*   ComportementPersoMultiples::getInstance(std::vector<Comportement*> ListComportement)
{
    if (singletonPersoMultiples == nullptr)
        singletonPersoMultiples = new ComportementPersoMultiples(ListComportement);

    return  singletonPersoMultiples;
}

ComportementPersoMultiples*   ComportementPersoMultiples::getInstance()
{
    if (singletonPersoMultiples == nullptr)
        std::cerr <<"ComportementPersoMultiples instance not initialized with ListComportement!" << std::endl;

    return  singletonPersoMultiples;
}

void ComportementPersoMultiples::bouge(Bestiole& bestiole, std::vector<EspeceBestiole*>   listeBestioles ) const 
{
    ListComportements[rand() % ListComportements.size()]->bouge(bestiole, listeBestioles);

}