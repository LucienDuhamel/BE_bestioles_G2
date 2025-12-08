#include "Bestiole.h"
#include "ComportementKamikaze.h"
#include "utils.h"

#include <iostream>
#include <vector>

ComportementKamikaze* ComportementKamikaze::singletonKamikaze = nullptr;
T ComportementKamikaze::couleur_cfg[3] = {0, 0, 0};
bool ComportementKamikaze::configInitialized = false;

ComportementKamikaze* ComportementKamikaze::getInstance()  
{
    if (singletonKamikaze == nullptr){
        singletonKamikaze = new ComportementKamikaze();

        if(!configInitialized) {
            singletonKamikaze->initFromConfig();
            configInitialized = true;
        }

    }

    return  singletonKamikaze;
}

Comportement* ComportementKamikaze::clone() const {
    // Just return the singleton
    return getInstance();
}

void ComportementKamikaze::initFromConfig() {
    // par defaut : rouge
    couleur_cfg[0] = Config::getInstance().getInt("KAM_COULEUR_R", 200);
    couleur_cfg[1] = Config::getInstance().getDouble("KAM_COULEUR_G", 0);
    couleur_cfg[2] = Config::getInstance().getDouble("KAM_COULEUR_B", 0);
}

T * ComportementKamikaze::getCouleur()  const {
    return couleur_cfg;
}

void ComportementKamikaze::reagit( Bestiole& bestiole, const std::vector<EspeceBestiole*>& listeBestioles)
{
    const auto& bestiolesVisibles = bestiole.detecteBestioles(listeBestioles);

    if (bestiolesVisibles.empty()) return; 

    // Initialisation : on suppose la première bestiole comme cible
    EspeceBestiole* cible = bestiolesVisibles.front();
    double distanceMin = calcDistance(bestiole, *cible);

    // Recherche de la bestiole la plus proche
    for (EspeceBestiole* other : bestiolesVisibles)
    {   
        double d = calcDistance(bestiole, *other);
        if (d < distanceMin)
        {
            distanceMin = d;
            cible = other;
        }
    }

    // Ajuster l'orientation vers la cible
    bestiole.setOrientation(calcOrientation(bestiole, *cible));
}