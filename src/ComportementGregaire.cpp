#include "Bestiole.h"
#include "ComportementGregaire.h"
#include "utils.h"

#include <iostream>
#include <vector>

ComportementGregaire* ComportementGregaire::singletonGregaire = nullptr;

ComportementGregaire*  ComportementGregaire::getInstance()
{
    if (singletonGregaire == nullptr){
        singletonGregaire = new ComportementGregaire();
        singletonGregaire->couleur = new T[ 3 ];
        
        // Couleur orange
        singletonGregaire->couleur[ 0 ] = 255;
        singletonGregaire->couleur[ 1 ] = 128;
        singletonGregaire->couleur[ 2 ] = 0;

    }

    return  singletonGregaire;
}
T * ComportementGregaire::getCouleur() const {
    return couleur;
}
void ComportementGregaire::reagit( Bestiole& bestiole, const std::vector<EspeceBestiole*>& listeBestioles)
{
    const auto& liste = bestiole.detecteBestioles(listeBestioles);

    if (liste.empty()) return;   // éviter division par zéro

    double mOrientation = 0.0;

    for (EspeceBestiole* b : liste) {
        mOrientation += b->getOrientation();
    }

    mOrientation /= liste.size();
    bestiole.setOrientation(mOrientation);
}
