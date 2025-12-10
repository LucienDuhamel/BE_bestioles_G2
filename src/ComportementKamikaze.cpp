#include "Bestiole.h"
#include "ComportementKamikaze.h"
#include "utils.h"

#include <iostream>
#include <vector>

ComportementKamikaze* ComportementKamikaze::singletonKamikaze = nullptr;
T ComportementKamikaze::COULEUR_CFG[3] = {0, 0, 0};
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
    return getInstance();
}


/**
 * @brief Comportement kamikaze : oriente la bestiole vers l'especeBestiole la plus proche.
 * 
 * La bestiole fonce droit sur l'especeBestiole la plus proche détecté.
 * 
 * @param bestiole La bestiole qui adopte ce comportement
 * @param listeBestioles Liste de toutes les bestioles du milieu
 * 
 * @details
 * - Détecte les bestioles visibles selon les capteurs
 * - Identifie la bestiole la plus proche (distance euclidienne)
 * - Oriente directement vers la cible (pas d'anticipation)
 * 
 * @note Aucun changement de vitesse, uniquement l'orientation.
 */
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

    bestiole.setOrientation(calcOrientation(bestiole, *cible));
}

T * ComportementKamikaze::getCouleur()  const {
    return COULEUR_CFG;
}

void ComportementKamikaze::initFromConfig() {
    // par defaut : rouge
    COULEUR_CFG[0] = Config::getInstance().getInt("KAM_COULEUR_R", 200);
    COULEUR_CFG[1] = Config::getInstance().getDouble("KAM_COULEUR_G", 0);
    COULEUR_CFG[2] = Config::getInstance().getDouble("KAM_COULEUR_B", 0);
}