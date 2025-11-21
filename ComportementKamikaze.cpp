#include "Bestiole.h"
#include "ComportementKamikaze.h"
#include <iostream>
#include <vector>


ComportementKamikaze* ComportementKamikaze::singletonKamikaze = nullptr;


ComportementKamikaze*   ComportementKamikaze::getInstance()
{
    if (singletonKamikaze == nullptr){
        singletonKamikaze = new ComportementKamikaze();
        singletonKamikaze->couleur = new T[ 3 ];
        singletonKamikaze->couleur[ 0 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );
        singletonKamikaze->couleur[ 1 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );
        singletonKamikaze->couleur[ 2 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );

    }

    return  singletonKamikaze;
}

T * ComportementKamikaze::getCouleur()  const {
    return couleur;
}

void ComportementKamikaze::bouge(Bestiole& bestiole, std::vector<EspeceBestiole*>   listeBestioles ) const 
{
    
}