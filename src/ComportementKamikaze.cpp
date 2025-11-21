#include "Bestiole.h"
#include "ComportementKamikaze.h"
#include "utils.h"

#include <iostream>
#include <vector>


ComportementKamikaze* ComportementKamikaze::singletonKamikaze = nullptr;


ComportementKamikaze*   ComportementKamikaze::getInstance()
{
    if (singletonKamikaze == nullptr)
        singletonKamikaze = new ComportementKamikaze();

    return  singletonKamikaze;
}


void ComportementKamikaze::bouge( Bestiole& bestiole, const std::vector<EspeceBestiole*>& listeBestioles) const
{
    const auto& bestiolesVisibles = bestiole.detecteBestioles(listeBestioles);

    if (bestiolesVisibles.empty())
        return; 

    // Initialisation : on suppose la première bestiole comme cible
    Bestiole* cible = bestiolesVisibles.front();
    double distanceMin = calcDistance(bestiole, *cible);

    // Recherche de la bestiole la plus proche
    for (Bestiole* autre : bestiolesVisibles)
    {
        double d = calcDistance(bestiole, *autre);
        if (d < distanceMin)
        {
            distanceMin = d;
            cible = autre;
        }
    }

    // Ajuster l'orientation vers la cible
    bestiole.setOrientation(calcOrientation(bestiole, *cible));

}