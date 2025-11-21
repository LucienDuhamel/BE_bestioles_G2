#include "Bestiole.h"
#include "ComportementGregaire.h"
#include <iostream>
#include <vector>

ComportementGregaire* ComportementGregaire::singletonGregaire = nullptr;

ComportementGregaire*  ComportementGregaire::getInstance()
{
    if (singletonGregaire == nullptr){
        singletonGregaire = new ComportementGregaire();
        singletonGregaire->couleur = new T[ 3 ];
        singletonGregaire->couleur[ 0 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );
        singletonGregaire->couleur[ 1 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );
        singletonGregaire->couleur[ 2 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );

    }

    return  singletonGregaire;
}
T * ComportementGregaire::getCouleur() const {
    return couleur;
}
void ComportementGregaire::bouge(Bestiole& bestiole, std::vector<EspeceBestiole*>   listeBestioles ) const 
{

}