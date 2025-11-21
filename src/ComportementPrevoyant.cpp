#include "Bestiole.h"
#include "ComportementPrevoyant.h"
#include <iostream>
#include <vector>


ComportementPrevoyant* ComportementPrevoyant::singletonPrevoyant = nullptr;

ComportementPrevoyant*   ComportementPrevoyant::getInstance()
{
    if (singletonPrevoyant == nullptr){
        singletonPrevoyant = new ComportementPrevoyant();
        singletonPrevoyant->couleur = new T[ 3 ];
        singletonPrevoyant->couleur[ 0 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );
        singletonPrevoyant->couleur[ 1 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );
        singletonPrevoyant->couleur[ 2 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );

    }

    return  singletonPrevoyant;
}

T * ComportementPrevoyant::getCouleur()  const {
    return couleur;
}
void ComportementPrevoyant::bouge(Bestiole& bestiole, std::vector<EspeceBestiole*>   listeBestioles ) const 
{
    
}