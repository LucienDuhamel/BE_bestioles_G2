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

        // Couleur rouge foncé
        singletonKamikaze->couleur[ 0 ] = 200;
        singletonKamikaze->couleur[ 1 ] = 0;
        singletonKamikaze->couleur[ 2 ] = 0;

    }

    return  singletonKamikaze;
}

T * ComportementKamikaze::getCouleur()  const {
    return couleur;
}

void ComportementKamikaze::reagit( Bestiole& bestiole, const std::vector<EspeceBestiole*>& listeBestioles) const
{
    const auto& bestiolesVisibles = bestiole.detecteBestioles(listeBestioles);

    if (bestiolesVisibles.empty())
        return; 

    // Initialisation : on suppose la première bestiole comme cible
    EspeceBestiole* cible = bestiolesVisibles.front();
    double distanceMin = calcDistance(bestiole, *cible);

    // Recherche de la bestiole la plus proche
    for (EspeceBestiole* autre : bestiolesVisibles)
    {
        double d = calcDistance(bestiole, *autre);
        if (d < distanceMin)
        {
            distanceMin = d;
            cible = autre;
        }
    }

    // Ajuster l'orientation vers la cible
    bestiole.setorientation(calcOrientation(bestiole, *cible));
}