#include "Bestiole.h"
#include "ComportementPeureux.h"
#include <iostream>
#include <vector>


ComportementPeureux* ComportementPeureux::singletonPeureux = nullptr;



ComportementPeureux*   ComportementPeureux::getInstance()
{
    if (singletonPeureux == nullptr){
        singletonPeureux = new ComportementPeureux();
        singletonPeureux->couleur = new T[ 3 ];
        singletonPeureux->couleur[ 0 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );
        singletonPeureux->couleur[ 1 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );
        singletonPeureux->couleur[ 2 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );

    }

    return  singletonPeureux;
}

T * ComportementPeureux::getCouleur()  const  {
    return couleur;
}
void ComportementPeureux::bouge(Bestiole& bestiole, std::vector<EspeceBestiole*>   listeBestioles ) const 
{
    
}