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
    if (singletonPersoMultiples == nullptr){
        singletonPersoMultiples = new ComportementPersoMultiples(ListComportement);
        singletonPersoMultiples->couleur = new T[ 3 ];
        singletonPersoMultiples->couleur[ 0 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );
        singletonPersoMultiples->couleur[ 1 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );
        singletonPersoMultiples->couleur[ 2 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );

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
void ComportementPersoMultiples::bouge(Bestiole& bestiole, std::vector<EspeceBestiole*>   listeBestioles ) const 
{
    ListComportements[rand() % ListComportements.size()]->bouge(bestiole, listeBestioles);

}